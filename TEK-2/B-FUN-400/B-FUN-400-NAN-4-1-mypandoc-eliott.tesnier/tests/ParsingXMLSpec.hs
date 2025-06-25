{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- ParsingXMLSpec
-}

module ParsingXMLSpec (spec) where

import Test.Hspec
import Parser.ParserXML
import Parser.ParserGlobal (runParser)
import Document

spec :: Spec
spec = do
    describe "XML Parser Unit Tests" $ do
        describe "Basic XML Value Parsing" $ do
            it "parses text" $ do
                runParser parseXmlText "hello" `shouldBe` Just (XmlText "hello", "")

            it "parses comment" $ do
                runParser parseXmlComment "<!--comment-->" `shouldBe` Just (XmlComment "comment", "")

            it "parses CDATA" $ do
                runParser parseXmlCData "<![CDATA[data]]>" `shouldBe` Just (XmlCData "data", "")

            it "parses processing instruction" $ do
                runParser parseXmlProcessingInstruction "<?xml version=\"1.0\"?>" `shouldBe`
                    Just (XmlProcessingInstruction "xml" "version=\"1.0\"", "")

            it "parses doctype" $ do
                runParser parseXmlDoctype "<!DOCTYPE html>" `shouldBe` Just (XmlDoctype "html", "")

        describe "Element Parsing" $ do
            it "parses empty element" $ do
                runParser parseXmlElement "<tag/>" `shouldBe`
                    Just (XmlElement "tag" [] [], "")

            it "parses element with attributes" $ do
                runParser parseXmlElement "<tag attr=\"value\"/>" `shouldBe`
                    Just (XmlElement "tag" [("attr", "value")] [], "")

            it "parses element with content" $ do
                runParser parseXmlElement "<tag>content</tag>" `shouldBe`
                    Just (XmlElement "tag" [] [XmlText "content"], "")

            it "parses nested elements" $ do
                runParser parseXmlElement "<parent><child>text</child></parent>" `shouldBe`
                    Just (XmlElement "parent" [] [XmlElement "child" [] [XmlText "text"]], "")

        describe "Document Structure Conversion" $ do
            it "converts empty document" $ do
                parseXML "<document></document>" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing) [])

            it "converts document with header" $ do
                parseXML "<document><header title=\"Test\"></header></document>" `shouldBe`
                    Just (Document (Header "Test" Nothing Nothing) [])

            it "converts complete document header" $ do
                parseXML "<document><header title=\"Test\"><author>John</author><date>2024</date></header></document>" `shouldBe`
                    Just (Document (Header "Test" (Just "John") (Just "2024")) [])

        describe "Content Conversion" $ do
            it "converts paragraph content" $ do
                parseXML "<document><body><paragraph>text</paragraph></body></document>" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing)
                                 [Paragraph [PlainText "text"]])

            it "converts bold text" $ do
                parseXML "<document><body><paragraph><bold>text</bold></paragraph></body></document>" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing)
                                 [Paragraph [Bold (PlainText "text"), PlainText " "]])

            it "converts section with correct level" $ do
                parseXML "<document><body><section title=\"S1\"><section title=\"S2\"></section></section></body></document>" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing)
                                 [Section 1 "S1" [Section 2 "S2" []]])

            it "converts link element" $ do
                parseXML "<document><body><paragraph><link url=\"https://example.com\">Link text</link></paragraph></body></document>" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing)
                                 [Paragraph [Link "Link text" "https://example.com", PlainText ""]])

            it "converts image element" $ do
                parseXML "<document><body><paragraph><image url=\"image.jpg\">Alt text</image></paragraph></body></document>" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing)
                                 [Paragraph [PlainText " ", Image "Alt text" "image.jpg", PlainText ""]])

            it "converts code block" $ do
                parseXML "<document><body><codeblock>code</codeblock></body></document>" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing)
                                 [CodeBlock [Paragraph [PlainText "code"]]])

            it "converts list with items" $ do
                parseXML "<document><body><list><paragraph>item 1</paragraph><paragraph>item 2</paragraph></list></body></document>" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing)
                                 [List [Item [PlainText "item 1"], Item [PlainText "item 2"]]])