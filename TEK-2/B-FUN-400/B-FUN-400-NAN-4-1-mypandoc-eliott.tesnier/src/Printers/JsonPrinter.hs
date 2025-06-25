{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- JsonPrinter
-}

module Printers.JsonPrinter (printJson) where

import Document
import Data.List (intercalate)
import Data.Maybe (catMaybes)

indent :: Int -> String
indent n = replicate (n * 4) ' '

quote :: String -> String
quote s = '"' : concatMap escape s ++ "\""
  where
    escape '"'  = "\\\""
    escape '\\' = "\\\\"
    escape '\n'  = "\\n"
    escape c     = [c]

flatten :: Content -> String
flatten (PlainText t)   = t
flatten (Bold c)        = flatten c
flatten (Italic c)      = flatten c
flatten (InLineCode c)  = c
flatten _               = ""

printJson :: Document -> String
printJson (Document (Header title author date) contents) =
  "{\n" ++
  printHeader title author date ++ ",\n" ++
  printBody contents ++ "\n" ++
  "}\n"

printHeader :: String -> Maybe String -> Maybe String -> String
printHeader title author date =
  indent 1 ++ "\"header\": {\n" ++
  intercalate ",\n" (catMaybes
    [ Just $ indent 2 ++ "\"title\": " ++ quote title
    , fmap (\a -> indent 2 ++ "\"author\": " ++ quote a) author
    , fmap (\d -> indent 2 ++ "\"date\": " ++ quote d) date
    ]) ++ "\n" ++
  indent 1 ++ "}"

printBody :: [Content] -> String
printBody contents =
  indent 1 ++ "\"body\": [\n" ++
  intercalate ",\n" (map (printElement 2) contents) ++ "\n" ++
  indent 1 ++ "]"

printElement :: Int -> Content -> String
printElement lvl (Paragraph inls) =
  let elems = filter (not . null) $ map (printInline (lvl + 1)) inls
  in indent lvl ++ "[\n" ++
     intercalate ",\n" elems ++ "\n" ++
     indent lvl ++ "]"
printElement lvl (Section _ title subs) =
  indent lvl ++ "{\n" ++
  indent (lvl + 1) ++ "\"section\": {\n" ++
  indent (lvl + 2) ++ "\"title\": " ++ quote title ++ ",\n" ++
  indent (lvl + 2) ++ "\"content\": [\n" ++
  intercalate ",\n" (map (printElement (lvl + 3)) subs) ++ "\n" ++
  indent (lvl + 2) ++ "]\n" ++
  indent (lvl + 1) ++ "}\n" ++
  indent lvl ++ "}"
printElement lvl (CodeBlock code) =
  indent lvl ++ "{\n" ++
  indent (lvl + 1) ++ "\"codeblock\": [\n" ++
  intercalate ",\n" (map (printCodeContent (lvl + 2)) code) ++ "\n" ++
  indent (lvl + 1) ++ "]\n" ++
  indent lvl ++ "}"
printElement lvl (List items) =
  indent lvl ++ "{\n" ++
  indent (lvl + 1) ++ "\"list\": [\n" ++
  intercalate ",\n" (map (printItem (lvl + 2)) items) ++ "\n" ++
  indent (lvl + 1) ++ "]\n" ++
  indent lvl ++ "}"
printElement _ _ = ""

printItem :: Int -> Item -> String
printItem lvl (Item inls) =
  let elems = filter (not . null) $ map (printInline (lvl + 1)) inls
  in indent lvl ++ "[\n" ++
     intercalate ",\n" elems ++ "\n" ++
     indent lvl ++ "]"

printInline :: Int -> Content -> String
printInline lvl (PlainText t)  = printPlain lvl t
printInline lvl (Bold c)       = printBold lvl c
printInline lvl (Italic c)     = printItalic lvl c
printInline lvl (InLineCode c) = printCode lvl c
printInline lvl (Link t u)     = printLink lvl t u
printInline lvl (Image a u)    = printImage lvl a u
printInline _   _              = ""

printPlain :: Int -> String -> String
printPlain lvl t
  | null t || all (== ' ') t = ""
  | otherwise                = indent lvl ++ quote t

printBold :: Int -> Content -> String
printBold lvl c =
  indent lvl ++ "{\n" ++
  indent (lvl + 1) ++ "\"bold\": " ++ quote (flatten c) ++ "\n" ++
  indent lvl ++ "}"

printItalic :: Int -> Content -> String
printItalic lvl c =
  indent lvl ++ "{\n" ++
  indent (lvl + 1) ++ "\"italic\": " ++ quote (flatten c) ++ "\n" ++
  indent lvl ++ "}"

printCode :: Int -> String -> String
printCode lvl c =
  indent lvl ++ "{\n" ++
  indent (lvl + 1) ++ "\"code\": " ++ quote c ++ "\n" ++
  indent lvl ++ "}"

printLink :: Int -> String -> String -> String
printLink lvl t u =
  indent lvl ++ "{\n" ++
  indent (lvl + 1) ++ "\"link\": {\n" ++
  indent (lvl + 2) ++ "\"url\": " ++ quote u ++ ",\n" ++
  indent (lvl + 2) ++ "\"content\": [\n" ++
  indent (lvl + 3) ++ quote t ++ "\n" ++
  indent (lvl + 2) ++ "]\n" ++
  indent (lvl + 1) ++ "}\n" ++
  indent lvl ++ "}"

printImage :: Int -> String -> String -> String
printImage lvl a u =
  indent lvl ++ "{\n" ++
  indent (lvl + 1) ++ "\"image\": {\n" ++
  indent (lvl + 2) ++ "\"url\": " ++ quote u ++ ",\n" ++
  indent (lvl + 2) ++ "\"alt\": [\n" ++
  indent (lvl + 3) ++ quote a ++ "\n" ++
  indent (lvl + 2) ++ "]\n" ++
  indent (lvl + 1) ++ "}\n" ++
  indent lvl ++ "}"

printCodeContent :: Int -> Content -> String
printCodeContent lvl (PlainText text) = indent lvl ++ quote text
printCodeContent lvl (Paragraph [PlainText text]) = indent lvl ++ quote text
printCodeContent lvl (Paragraph contents) =
  intercalate ",\n" (map (printCodeContent lvl) contents)
printCodeContent lvl content = printElement lvl content