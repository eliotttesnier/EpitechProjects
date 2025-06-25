{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- Parser
-}

module Parser.Parser
    ( parseDocument
    , detectFormat
    ) where

import Document
import Parser.ParserJSON as JSON
import Parser.ParserXML as XML
import Data.Char (isSpace)

skipWhitespace :: String -> String
skipWhitespace = dropWhile isSpace

isJSON :: String -> Bool
isJSON s = case skipWhitespace s of
    '{':_ -> True
    '[':_ -> True
    _ -> False

isXML :: String -> Bool
isXML s = case skipWhitespace s of
    '<':_ -> True
    _ -> False

detectFormat :: String -> String
detectFormat content
    | isJSON content = "json"
    | isXML content = "xml"
    | otherwise = ""

parseDocument :: FilePath -> String -> String -> Maybe Document
parseDocument _ content "json" = JSON.parseJSON content
parseDocument _ content "xml" = XML.parseXML content
parseDocument _ content ""
    | isJSON content = JSON.parseJSON content
    | isXML content = XML.parseXML content
    | otherwise = Nothing
parseDocument _ _ "markdown" = Nothing
parseDocument _ _ _ = Nothing
