{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- ParserXML
-}

module Parser.ParserXML
    ( parseXML
    , XmlValue(..)
    , parseXmlElement
    , parseXmlText
    , parseXmlComment
    , parseXmlCData
    , parseXmlProcessingInstruction
    , parseXmlDoctype
    ) where

import Parser.ParserGlobal
import Document
import Control.Applicative (Alternative(..))
import qualified Data.Char as Char

data XmlValue
  = XmlText String
  | XmlElement String [(String, String)] [XmlValue]
  | XmlComment String
  | XmlCData String
  | XmlProcessingInstruction String String
  | XmlDoctype String
  deriving (Show, Eq)

parseXmlText :: Parser XmlValue
parseXmlText = do
  text <- parseSome (parseIf (/= '<'))
  return (XmlText text)

parseXmlName :: Parser String
parseXmlName = do
  first <- parseIf isNameStartChar
  rest <- parseMany (parseIf isNameChar)
  return (first : rest)
  where
    isNameStartChar c = Char.isAlpha c || c == '_' || c == ':'
    isNameChar c = isNameStartChar c || Char.isDigit c || c == '-' || c == '.'

parseXmlAttribute :: Parser (String, String)
parseXmlAttribute = do
  _ <- parseSpaces
  name <- parseXmlName
  _ <- parseSpaces
  _ <- parseChar '='
  _ <- parseSpaces
  _ <- parseChar '"'
  value <- parseMany (parseIf (/= '"'))
  _ <- parseChar '"'
  return (name, value)

parseXmlAttributes :: Parser [(String, String)]
parseXmlAttributes = parseMany parseXmlAttribute

parseXmlComment :: Parser XmlValue
parseXmlComment = do
  _ <- parseString "<!--"
  comment <- parseMany (parseIf (/= '-'))
  _ <- parseString "-->"
  return (XmlComment comment)

parseXmlCData :: Parser XmlValue
parseXmlCData = do
  _ <- parseString "<![CDATA["
  content <- parseMany (parseIf (/= ']'))
  _ <- parseString "]]>"
  return (XmlCData content)

parseXmlProcessingInstruction :: Parser XmlValue
parseXmlProcessingInstruction = do
  _ <- parseString "<?"
  target <- parseXmlName
  _ <- parseSpaces
  content <- parseMany (parseIf (/= '?'))
  _ <- parseString "?>"
  return (XmlProcessingInstruction target content)

parseXmlDoctype :: Parser XmlValue
parseXmlDoctype = do
  _ <- parseString "<!DOCTYPE"
  _ <- parseSpaces
  definition <- parseMany (parseIf (/= '>'))
  _ <- parseChar '>'
  return (XmlDoctype definition)

parseXmlContent :: Parser [XmlValue]
parseXmlContent = parseMany parseXmlValue

parseXmlValue :: Parser XmlValue
parseXmlValue = token $
  parseXmlComment <|>
  parseXmlCData <|>
  parseXmlProcessingInstruction <|>
  parseXmlElement <|>
  parseXmlText

parseXmlElementContent :: String -> Parser [XmlValue]
parseXmlElementContent name =
  (parseChar '/' >> parseChar '>' >> return [])
  <|> (parseChar '>' >> parseElementContent name)

parseElementContent :: String -> Parser [XmlValue]
parseElementContent name = do
  content <- parseXmlContent
  _ <- parseString ("</" ++ name ++ ">")
  return content

parseXmlElement :: Parser XmlValue
parseXmlElement = do
  _ <- parseChar '<'
  name <- parseXmlName
  attributes <- parseXmlAttributes
  content <- parseXmlElementContent name
  return (XmlElement name attributes content)

parseXML :: String -> Maybe Document
parseXML input = case runParser parseXmlValue input of
  Nothing -> Nothing
  Just (xml, _) -> Just (convertXmlToDocument xml)

convertXmlToDocument :: XmlValue -> Document
convertXmlToDocument (XmlElement "document" _ contents) =
  let header = extractHeaderFromXml contents
      body = extractBodyFromXml contents
  in createStructuredDocument header body
convertXmlToDocument _ =
  createStructuredDocument (Header "Untitled Document" Nothing Nothing) []

extractHeaderFromXml :: [XmlValue] -> Header
extractHeaderFromXml values =
  case findElement "header" values of
    Just (XmlElement _ attrs children) ->
      Header (lookupAttr "title" attrs "Untitled Document")
             (findTextContent "author" children)
             (findTextContent "date" children)
    _ -> Header "Untitled Document" Nothing Nothing

extractBodyFromXml :: [XmlValue] -> [Content]
extractBodyFromXml values =
  case findElement "body" values of
    Just (XmlElement _ _ children) -> map (xmlValueToContent 0) children
    _ -> []

addSpacesAfterContent :: String -> Maybe Char -> String
addSpacesAfterContent _ (Just '.') = ""
addSpacesAfterContent _ (Just ',') = ""
addSpacesAfterContent _ (Just ';') = ""
addSpacesAfterContent _ (Just ':') = ""
addSpacesAfterContent _ (Just '!') = ""
addSpacesAfterContent _ (Just '?') = ""
addSpacesAfterContent "link" _ = ""
addSpacesAfterContent "image" _ = ""
addSpacesAfterContent _ _ = " "

extractFirstChar :: [XmlValue] -> Int -> Maybe Char
extractFirstChar values index =
  if index < length values - 1
  then case values !! (index + 1) of
    XmlText (c:_) -> Just c
    _ -> Nothing
  else Nothing

xmlValueToContent :: Int -> XmlValue -> Content
xmlValueToContent _ (XmlText text) = PlainText text
xmlValueToContent depth (XmlElement name attrs children) =
  case name of
    "paragraph" -> Paragraph (processInlineContent children)
    "section" ->
      let title = lookupAttr "title" attrs ""
          nextDepth = depth + 1
      in Section nextDepth title (map (xmlValueToContent nextDepth) children)
    "codeblock" -> CodeBlock (extractCodeBlockContent children)
    "list" -> List (map elementToItem children)
    _ -> PlainText ""
xmlValueToContent _ _ = PlainText ""

elementToItem :: XmlValue -> Item
elementToItem (XmlElement "paragraph" _ children) =
  Item (map PlainText (extractAllText children))
elementToItem _ = Item []

removeTrailingSpace :: [Content] -> [Content]
removeTrailingSpace [] = []
removeTrailingSpace [x] = [x]
removeTrailingSpace contents =
  let init_content = take (length contents - 1) contents
      last_content = last contents
  in case last_content of
        PlainText " " -> init_content
        _ -> contents

processInlineContent :: [XmlValue] -> [Content]
processInlineContent values = removeTrailingSpace $
                              concatMap processWithContext (zip values [0..])
  where
    processWithContext (element, index) =
      elementToInlineContent element (extractFirstChar values index)

createBoldContent :: [XmlValue] -> String -> [Content]
createBoldContent ch space = [Bold (PlainText (concatMap extractText ch)),
                              PlainText space]

createItalicContent :: [XmlValue] -> String -> [Content]
createItalicContent ch space = [Italic (PlainText (concatMap extractText ch)),
                                PlainText space]

createCodeContent :: [XmlValue] -> String -> [Content]
createCodeContent ch space = [InLineCode (concatMap extractText ch),
                              PlainText space]

createLinkContent :: [XmlValue] -> [(String, String)] -> String -> [Content]
createLinkContent ch attrs space =
    [Link (concatMap extractText ch) (lookupAttr "url" attrs ""),
    PlainText space]

createImageContent :: [XmlValue] -> [(String, String)] -> String -> [Content]
createImageContent ch attrs space = [PlainText " ",
    Image (concatMap extractText ch) (lookupAttr "url" attrs ""),
    PlainText space]

elementToInlineContent :: XmlValue -> Maybe Char -> [Content]
elementToInlineContent (XmlText text) _ = [PlainText text]
elementToInlineContent (XmlElement name attrs children) nextChar =
  let space = addSpacesAfterContent name nextChar in
  case name of
    "bold" -> createBoldContent children space
    "italic" -> createItalicContent children space
    "code" -> createCodeContent children space
    "link" -> createLinkContent children attrs space
    "image" -> createImageContent children attrs space
    _ -> []
elementToInlineContent _ _ = []

extractCodeBlockContent :: [XmlValue] -> [Content]
extractCodeBlockContent values =
  map (\v -> Paragraph [PlainText (extractText v)]) values

extractAllText :: [XmlValue] -> [String]
extractAllText = map extractText

extractText :: XmlValue -> String
extractText (XmlText text) = text
extractText (XmlElement _ _ children) = concatMap extractText children
extractText _ = ""

findElement :: String -> [XmlValue] -> Maybe XmlValue
findElement _ [] = Nothing
findElement name (e@(XmlElement n _ _):xs)
  | name == n = Just e
  | otherwise = findElement name xs
findElement name (_:xs) = findElement name xs

findTextContent :: String -> [XmlValue] -> Maybe String
findTextContent name values =
  case findElement name values of
    Just (XmlElement _ _ children) -> Just (concatMap extractText children)
    _ -> Nothing

lookupAttr :: String -> [(String, String)] -> String -> String
lookupAttr key attrs defaultValue =
  case lookup key attrs of
    Just value -> value
    Nothing -> defaultValue

