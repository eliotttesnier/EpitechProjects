{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- PrinterXMLSpec
-}

module PrinterXMLSpec (spec) where

import Test.Hspec
import Printers.XmlPrinter
import Document

spec :: Spec
spec = do
    describe "XML Printer Unit Tests" $ do
        describe "Header Printing" $ do
            it "prints header with title only" $ do
                let header = Header "Test Title" Nothing Nothing
                printXmlHeader header `shouldBe` "\t<header title=\"Test Title\">\n\t</header>\n"

            it "prints header with title and author" $ do
                let header = Header "Test Title" (Just "Test Author") Nothing
                printXmlHeader header `shouldBe` "\t<header title=\"Test Title\">\n\t\t<author>Test Author</author>\n\t</header>\n"

            it "prints header with title, author, and date" $ do
                let header = Header "Test Title" (Just "Test Author") (Just "2025-01-01")
                printXmlHeader header `shouldBe` "\t<header title=\"Test Title\">\n\t\t<author>Test Author</author>\n\t\t<date>2025-01-01</date>\n\t</header>\n"

            it "prints header with title and date" $ do
                let header = Header "Test Title" Nothing (Just "2025-01-01")
                printXmlHeader header `shouldBe` "\t<header title=\"Test Title\">\n\t\t<date>2025-01-01</date>\n\t</header>\n"

        describe "Content Printing" $ do
            it "prints plain text" $ do
                let content = PlainText "Hello, World!"
                printXmlContent 0 content `shouldBe` ""

            it "prints paragraph" $ do
                let content = Paragraph [PlainText "This is a paragraph."]
                printXmlContent 0 content `shouldBe` "<paragraph>This is a paragraph.</paragraph>\n"

            it "prints section with heading and contents" $ do
                let content = Section 1 "Section Title" [PlainText "This is a section."]
                printXmlContent 0 content `shouldBe` "<section title=\"Section Title\">\n</section>\n"

            it "prints code block" $ do
                let content = CodeBlock [Paragraph [PlainText "print('Hello, World!')"]]
                printXmlContent 0 content `shouldBe` "<codeblock>\n\t<paragraph>print('Hello, World!')</paragraph>\n</codeblock>\n"

            it "prints list" $ do
                let content = List [Item [PlainText "Item 1"], Item [PlainText "Item 2"]]
                printXmlContent 0 content `shouldBe` "<list>\n\t<paragraph>Item 1</paragraph>\n\t<paragraph>Item 2</paragraph>\n</list>\n"

        describe "Document Printing" $ do
            it "prints document with header and body" $ do
                let header = Header "Test Title" (Just "Test Author") (Just "2025-01-01")
                    content = Paragraph [PlainText "This is a paragraph."]
                    document = Document header [content]
                printXml document `shouldBe` "<document>\n" ++
                    "\t<header title=\"Test Title\">\n" ++
                    "\t\t<author>Test Author</author>\n" ++
                    "\t\t<date>2025-01-01</date>\n" ++
                    "\t</header>\n" ++
                    "\t<body>\n" ++
                    "\t\t<paragraph>This is a paragraph.</paragraph>\n" ++
                    "\t</body>\n" ++
                    "</document>\n"