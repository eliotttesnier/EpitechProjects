{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- MarkdownPrinter
-}

module Printers.MarkdownPrinter where

import Document

printMarkdownHeader :: Header -> String
printMarkdownHeader (Header docTitle docAuthor docDate) =
    "---\n" ++
    "title: " ++ docTitle ++ "\n" ++
    maybe "" (\a -> "author: " ++ a ++ "\n") docAuthor ++
    maybe "" (\d -> "date: " ++ d ++ "\n") docDate ++
    "---\n"

printMarkdownContent :: Content -> String
printMarkdownContent (PlainText text) = text
printMarkdownContent (Bold content) =
    "**" ++ printMarkdownContent content ++ "**"
printMarkdownContent (Italic content) =
    "*" ++ printMarkdownContent content ++ "*"
printMarkdownContent (InLineCode code) = "`" ++ code ++ "`"
printMarkdownContent (Link text url) = "[" ++ text ++ "](" ++ url ++ ")"
printMarkdownContent (Image alt url) = "![" ++ alt ++ "](" ++ url ++ ")"
printMarkdownContent (Paragraph contents) =
    concatMap printMarkdownContent contents ++ "\n\n"
printMarkdownContent (Section level heading contents)
    | null heading = concatMap printMarkdownContent contents
    | otherwise = replicate level '#' ++ " " ++ heading ++ "\n\n" ++
                 concatMap printMarkdownContent contents
printMarkdownContent (CodeBlock code) = "```\n" ++ concatMap
    printMarkdownContent code ++ "\n```\n"
printMarkdownContent (List items) = concatMap printMarkdownItem items ++ "\n"

printMarkdownItem :: Item -> String
printMarkdownItem (Item contents) =
    "- " ++ concatMap printMarkdownContent contents ++ "\n"

printMarkdownContents :: [Content] -> String
printMarkdownContents = concatMap printMarkdownContent

printMarkdown :: Document -> String
printMarkdown (Document header contents) =
    printMarkdownHeader header ++ "\n" ++ printMarkdownContents contents
        ++ "\n"
