{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- PrinterMDSpec
-}

module PrinterMDSpec (spec) where

import Test.Hspec
import Printers.MarkdownPrinter
import Document

spec :: Spec
spec = do
    describe "Markdown Printer Unit Tests" $ do
        describe "Header Printing" $ do
            it "prints header with title only" $ do
                let header = Header "Test Title" Nothing Nothing
                printMarkdownHeader header `shouldBe` "---\ntitle: Test Title\n---\n"

            it "prints header with title and author" $ do
                let header = Header "Test Title" (Just "Test Author") Nothing
                printMarkdownHeader header `shouldBe` "---\ntitle: Test Title\nauthor: Test Author\n---\n"

            it "prints header with title, author, and date" $ do
                let header = Header "Test Title" (Just "Test Author") (Just "2025-01-01")
                printMarkdownHeader header `shouldBe` "---\ntitle: Test Title\nauthor: Test Author\ndate: 2025-01-01\n---\n"

            it "prints header with title and date" $ do
                let header = Header "Test Title" Nothing (Just "2025-01-01")
                printMarkdownHeader header `shouldBe` "---\ntitle: Test Title\ndate: 2025-01-01\n---\n"

        describe "Content Printing" $ do
            it "prints plain text" $ do
                let content = PlainText "Hello, World!"
                printMarkdownContent content `shouldBe` "Hello, World!"

            it "prints bold text" $ do
                let content = Bold (PlainText "Bold Text")
                printMarkdownContent content `shouldBe` "**Bold Text**"

            it "prints italic text" $ do
                let content = Italic (PlainText "Italic Text")
                printMarkdownContent content `shouldBe` "*Italic Text*"

            it "prints inline code" $ do
                let content = InLineCode "code()"
                printMarkdownContent content `shouldBe` "`code()`"

            it "prints link" $ do
                let content = Link "Google" "https://www.google.com"
                printMarkdownContent content `shouldBe` "[Google](https://www.google.com)"

            it "prints image" $ do
                let content = Image "" "https://www.example.com/image.png"
                printMarkdownContent content `shouldBe` "![](https://www.example.com/image.png)"

            it "prints paragraph" $ do
                let content = Paragraph [PlainText "This is a paragraph."]
                printMarkdownContent content `shouldBe` "This is a paragraph.\n\n"

            it "prints section with heading and contents" $ do
                let content = Section 2 "Section Heading" [PlainText "Section Content"]
                printMarkdownContent content `shouldBe` "## Section Heading\n\nSection Content"

            it "prints code block" $ do
                let content = CodeBlock [Paragraph [PlainText "print('Hello, World!')"]]
                printMarkdownContent content `shouldBe` "```\nprint('Hello, World!')\n```\n"

            it "prints list with items" $ do
                let item1 = Item [PlainText "Item 1"]
                    item2 = Item [PlainText "Item 2"]
                    list = List [item1, item2]
                printMarkdownContent list `shouldBe` "- Item 1\n- Item 2\n\n"

            it "prints nested list" $ do
                let item1 = Item [PlainText "Item 1"]
                    item2 = Item [PlainText "Item 2"]
                    nestedItem = Item [PlainText "Nested Item"]
                    list = List [item1, item2, nestedItem]
                printMarkdownContent list `shouldBe` "- Item 1\n- Item 2\n- Nested Item\n\n"

        describe "Document Printing" $ do
            it "prints document with header and contents" $ do
                let header = Header "Test Document" (Just "Author") (Just "2025-01-01")
                    content1 = Paragraph [PlainText "This is a paragraph."]
                    content2 = Section 1 "Section 1" [PlainText "Section Content"]
                    doc = Document header [content1, content2]
                printMarkdown doc `shouldBe` "---\ntitle: Test Document\nauthor: Author\ndate: 2025-01-01\n---\n\nThis is a paragraph.\n\n# Section 1\n\nSection Content"