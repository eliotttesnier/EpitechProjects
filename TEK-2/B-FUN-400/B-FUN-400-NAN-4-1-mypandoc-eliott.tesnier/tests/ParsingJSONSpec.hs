{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- ParsingJSONSpec
-}

module ParsingJSONSpec (spec) where

import Test.Hspec
import Parser.ParserJSON
import Parser.ParserGlobal (runParser)
import Document

spec :: Spec
spec = do
    describe "JSON Parser Unit Tests" $ do
        describe "Basic JSON Value Parsing" $ do
            it "parses null" $ do
                runParser parseJsonNull "null" `shouldBe` Just (JsonNull, "")

            it "parses boolean true" $ do
                runParser parseJsonBool "true" `shouldBe` Just (JsonBool True, "")

            it "parses boolean false" $ do
                runParser parseJsonBool "false" `shouldBe` Just (JsonBool False, "")

            it "parses number" $ do
                runParser parseJsonNumber "42.5" `shouldBe` Just (JsonNumber 42.5, "")

            it "parses negative number" $ do
                runParser parseJsonNumber "-42.5" `shouldBe` Just (JsonNumber (-42.5), "")

            it "parses string" $ do
                runParser parseJsonString "\"hello\"" `shouldBe` Just (JsonString "hello", "")

        describe "Complex JSON Structure Parsing" $ do
            it "parses empty array" $ do
                runParser parseJsonArray "[]" `shouldBe` Just (JsonArray [], "")

            it "parses array with values" $ do
                runParser parseJsonArray "[1, 2, 3]" `shouldBe`
                    Just (JsonArray [JsonNumber 1.0, JsonNumber 2.0, JsonNumber 3.0], "")

            it "parses empty object" $ do
                runParser parseJsonObject "{}" `shouldBe` Just (JsonObject [], "")

            it "parses object with one pair" $ do
                runParser parseJsonObject "{\"key\": \"value\"}" `shouldBe`
                    Just (JsonObject [("key", JsonString "value")], "")

        describe "Document Structure Conversion" $ do
            it "converts empty object to document" $ do
                parseJSON "{}" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing) [])

            it "converts header object" $ do
                parseJSON "{\"header\":{\"title\":\"Test\"}}" `shouldBe`
                    Just (Document (Header "Test" Nothing Nothing) [])

            it "converts complete header" $ do
                parseJSON "{\"header\":{\"title\":\"Test\",\"author\":\"John\",\"date\":\"2024\"}}" `shouldBe`
                    Just (Document (Header "Test" (Just "John") (Just "2024")) [])

        describe "Content Conversion" $ do
            it "converts paragraph content" $ do
                parseJSON "{\"body\":[[\"text\"]]}" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing)
                                 [Paragraph [PlainText "text"]])

            it "converts bold text" $ do
                parseJSON "{\"body\":[[{\"bold\":\"text\"}]]}" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing)
                                 [Paragraph [Bold (PlainText "text")]])

            it "converts section with correct level" $ do
                parseJSON "{\"body\":[{\"section\":{\"title\":\"S1\",\"content\":[{\"section\":{\"title\":\"S2\"}}]}}]}" `shouldBe`
                    Just (Document (Header "Untitled Document" Nothing Nothing)
                                 [Section 1 "S1" [Section 2 "S2" []]])
