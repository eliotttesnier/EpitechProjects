{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- XmlPrinter
-}

module Printers.XmlPrinter where

import Document

tab :: Int -> String
tab n = replicate n '\t'

printXmlHeader :: Header -> String
printXmlHeader (Header title author date) =
    "\t<header title=\"" ++ title ++ "\">\n" ++
    maybe "" (\a -> "\t\t<author>" ++ a ++ "</author>\n") author ++
    maybe "" (\d -> "\t\t<date>" ++ d ++ "</date>\n") date ++
    "\t</header>\n"

printInlineContent :: Content -> String
printInlineContent (PlainText text) = text
printInlineContent (Bold content) =
    "<bold>" ++ printInlineContent content ++ "</bold>"
printInlineContent (Italic content) =
    "<italic>" ++ printInlineContent content ++ "</italic>"
printInlineContent (InLineCode code) = "<code>" ++ code ++ "</code>"
printInlineContent (Link text url) =
    "<link url=\"" ++ url ++ "\">" ++ text ++ "</link>"
printInlineContent (Image alt url) =
    "<image url=\"" ++ url ++ "\">" ++ alt ++ "</image>"
printInlineContent _ = ""

printXmlContent :: Int -> Content -> String
printXmlContent _ (PlainText _) = ""
printXmlContent _ (Bold _) = ""
printXmlContent _ (Italic _) = ""
printXmlContent _ (InLineCode _) = ""
printXmlContent _ (Link _ _) = ""
printXmlContent _ (Image _ _) = ""
printXmlContent depth (Paragraph contents) =
    tab depth ++ "<paragraph>" ++
    concatMap printInlineContent contents ++ "</paragraph>\n"
printXmlContent depth (Section _ heading contents) =
    tab depth ++ "<section title=\"" ++ heading ++ "\">\n" ++
    concatMap (printXmlContent (depth + 1)) contents ++
    tab depth ++ "</section>\n"
printXmlContent depth (CodeBlock code) =
    tab depth ++ "<codeblock>\n" ++
    concatMap (printCodeBlockContent (depth + 1)) code ++
    tab depth ++ "</codeblock>\n"
printXmlContent depth (List items) =
    tab depth ++ "<list>\n" ++
    concatMap (printXmlItem (depth + 1)) items ++
    tab depth ++ "</list>\n"

printXmlItem :: Int -> Item -> String
printXmlItem depth (Item contents) =
    tab depth ++ "<paragraph>" ++
    concatMap printInlineContent contents ++ "</paragraph>\n"

printXml :: Document -> String
printXml (Document header contents) =
    "<document>\n" ++
    printXmlHeader header ++
    "\t<body>\n" ++
    concatMap (printXmlContent 2) contents ++
    "\t</body>\n" ++
    "</document>\n"

printCodeBlockContent :: Int -> Content -> String
printCodeBlockContent depth (PlainText text) = 
    tab depth ++ text ++ "\n"
printCodeBlockContent depth (Paragraph contents) =
    tab depth ++ concatMap printInlineContent contents ++ "\n"
printCodeBlockContent depth content =
    printXmlContent depth content
