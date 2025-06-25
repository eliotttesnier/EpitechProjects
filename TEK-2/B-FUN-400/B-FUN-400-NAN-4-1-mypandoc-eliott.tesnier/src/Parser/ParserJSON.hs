{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- ParserJSON
-}

module Parser.ParserJSON
    ( parseJSON
    , JsonValue(..)
    , parseJsonNull
    , parseJsonBool
    , parseJsonNumber
    , parseJsonString
    , parseJsonArray
    , parseJsonObject
    ) where

import Parser.ParserGlobal
import Document
import Control.Applicative (Alternative(..))

data JsonValue
  = JsonNull
  | JsonBool Bool
  | JsonNumber Double
  | JsonString String
  | JsonArray [JsonValue]
  | JsonObject [(String, JsonValue)]
  deriving (Show, Eq)

parseJsonNull :: Parser JsonValue
parseJsonNull = do
  _ <- parseString "null"
  return JsonNull

parseJsonBool :: Parser JsonValue
parseJsonBool =
  (parseString "true" >> return (JsonBool True)) <|>
  (parseString "false" >> return (JsonBool False))

parseJsonNumber :: Parser JsonValue
parseJsonNumber = do
  sign <- parseChar '-' <|> return '+'
  n <- parseDouble
  return (JsonNumber (if sign == '-' then -n else n))

parseJsonString :: Parser JsonValue
parseJsonString = do
  _ <- parseChar '"'
  str <- parseMany (parseIf (/= '"'))
  _ <- parseChar '"'
  return (JsonString str)

parseJsonValue :: Parser JsonValue
parseJsonValue = token $
  parseJsonNull <|>
  parseJsonBool <|>
  parseJsonNumber <|>
  parseJsonString <|>
  parseJsonArray <|>
  parseJsonObject

parseJsonValueWithComma :: Parser JsonValue
parseJsonValueWithComma = do
    _ <- parseChar ','
    token parseJsonValue

parseJsonValueList :: Parser [JsonValue]
parseJsonValueList = do
    v <- token parseJsonValue
    vs <- parseMany parseJsonValueWithComma
    return (v:vs)

parseJsonValues :: Parser [JsonValue]
parseJsonValues = parseJsonValueList <|> return []

parseJsonArray :: Parser JsonValue
parseJsonArray = do
    _ <- parseChar '['
    _ <- parseSpaces
    values <- parseJsonValues
    _ <- parseChar ']'
    return (JsonArray values)

parseJsonPair :: Parser (String, JsonValue)
parseJsonPair = do
  _ <- parseSpaces
  _ <- parseChar '"'
  key <- parseMany (parseIf (/= '"'))
  _ <- parseChar '"'
  _ <- parseSpaces
  _ <- parseChar ':'
  value <- token parseJsonValue
  return (key, value)

parseJsonPairList :: Parser [(String, JsonValue)]
parseJsonPairList = do
  p <- parseJsonPair
  ps <- parseMany (parseChar ',' >> parseJsonPair)
  return (p:ps)

parseJsonPairs :: Parser [(String, JsonValue)]
parseJsonPairs = parseJsonPairList <|> return []

parseJsonObject :: Parser JsonValue
parseJsonObject = do
  _ <- parseChar '{'
  _ <- parseSpaces
  pairs <- parseJsonPairs
  _ <- parseChar '}'
  return (JsonObject pairs)

parseJSON :: String -> Maybe Document
parseJSON input = case runParser parseJsonValue input of
  Nothing -> Nothing
  Just (json, _) -> Just (convertJsonToDocument json)

convertJsonToDocument :: JsonValue -> Document
convertJsonToDocument (JsonObject pairs) =
  let headerVal = lookup "header" (normalizeKeys pairs)
      bodyVal   = lookup "body"   (normalizeKeys pairs)
      header    = extractHeaderFromHeaderSection headerVal
      content   = extractContentFromBody bodyVal
  in createStructuredDocument header content
convertJsonToDocument (JsonArray values) =
  createStructuredDocument (Header "Untitled Document" Nothing Nothing)
                         (map jsonValueToContent values)
convertJsonToDocument (JsonString s) =
  createStructuredDocument (Header "Untitled Document" Nothing Nothing)
                         [PlainText s]
convertJsonToDocument _ =
  createStructuredDocument (Header "Untitled Document" Nothing Nothing) []

extractHeaderFromHeaderSection :: Maybe JsonValue -> Header
extractHeaderFromHeaderSection (Just (JsonObject headerPairs)) =
  Header title' author' date'
  where
    title'  = extractStringValue headerPairs "title" "Untitled Document"
    author' = extractOptionalStringValue headerPairs "author"
    date'   = extractOptionalStringValue headerPairs "date"
extractHeaderFromHeaderSection _ =
  Header "Untitled Document" Nothing Nothing

extractContentFromBody :: Maybe JsonValue -> [Content]
extractContentFromBody (Just (JsonArray values)) =
  map jsonValueToContent values
extractContentFromBody (Just (JsonString s))     = [PlainText s]
extractContentFromBody _                         = []

extractSectionTitle :: [(String, JsonValue)] -> String
extractSectionTitle sectionPairs =
    maybe "" id $ extractOptionalStringValue sectionPairs "title"

extractSectionLevel :: Int -> [(String, JsonValue)] -> Int
extractSectionLevel parentLevel sectionPairs =
    case lookup "level" (normalizeKeys sectionPairs) of
        Just (JsonNumber n) -> floor n
        _ -> parentLevel + 1

handleSection :: Int -> [(String, JsonValue)] -> Content
handleSection parentLevel sectionPairs =
    let level = extractSectionLevel parentLevel sectionPairs
        title = extractSectionTitle sectionPairs
        content = case lookup "content" (normalizeKeys sectionPairs) of
            Just (JsonArray values) -> map (jsonValueToContent' level) values
            _ -> []
    in Section level title content

jsonValueToContent' :: Int -> JsonValue -> Content
jsonValueToContent' parentLevel (JsonObject pairs) =
    case lookup "section" (normalizeKeys pairs) of
        Just (JsonObject sectionPairs) ->
          handleSection parentLevel sectionPairs
        _ -> handleJsonObject pairs
jsonValueToContent' _ value = handlePlainContent value

handleJsonObject :: [(String, JsonValue)] -> Content
handleJsonObject pairs =
    case lookup "paragraph" (normalizeKeys pairs) of
        Just value -> jsonValueToContent value
        Nothing -> case lookup "section" (normalizeKeys pairs) of
            Just (JsonObject sectionPairs) -> handleSection 0 sectionPairs
            _ -> handleTextContent pairs

lookupAndHandle :: String -> (JsonValue -> Content) -> [(String, JsonValue)] -> Maybe Content
lookupAndHandle key handler pairs =
    fmap handler $ lookup key (normalizeKeys pairs)

tryHandleContent :: [(String, JsonValue)] -> [Maybe Content]
tryHandleContent pairs =
    [ lookupAndHandle "bold" (Bold . jsonValueToContent) pairs
    , lookupAndHandle "italic" (Italic . jsonValueToContent) pairs
    , lookupAndHandle "code" (InLineCode . extractStringContent) pairs
    , lookupAndHandle "link" handleLink pairs
    , lookupAndHandle "image" handleImage pairs
    , lookupAndHandle "codeblock" handleCodeBlock pairs
    , lookupAndHandle "list" handleList pairs
    ]

handleTextContent :: [(String, JsonValue)] -> Content
handleTextContent pairs = 
    case firstJust $ tryHandleContent pairs of
        Just content -> content
        Nothing -> PlainText (show (JsonObject pairs))

firstJust :: [Maybe a] -> Maybe a
firstJust = foldr (<|>) Nothing

handleLink :: JsonValue -> Content
handleLink (JsonObject pairs) =
    Link content url
    where
        content = extractStringValue pairs "content" ""
        url = extractStringValue pairs "url" ""
handleLink _ = PlainText ""

handleImage :: JsonValue -> Content
handleImage (JsonObject pairs) =
    Image alt url
    where
        alt = case lookup "alt" (normalizeKeys pairs) of
            Just (JsonArray [JsonString s]) -> s
            _ -> ""
        url = extractStringValue pairs "url" ""
handleImage _ = PlainText ""

extractStringContent :: JsonValue -> String
extractStringContent (JsonString s) = s
extractStringContent (JsonArray [JsonString s]) = s
extractStringContent _ = ""

makeListItem :: JsonValue -> Item
makeListItem (JsonArray contents) = Item (map jsonValueToContent contents)
makeListItem _ = Item []

handleCodeBlock :: JsonValue -> Content
handleCodeBlock (JsonObject pairs) = 
    CodeBlock (case lookup "content" (normalizeKeys pairs) of
        Just (JsonArray values) -> map jsonValueToContent values
        Just value -> [jsonValueToContent value]
        _ -> [])
handleCodeBlock (JsonArray values) =
  CodeBlock (map wrapStringInParagraph values)
handleCodeBlock (JsonString s) = CodeBlock [Paragraph [PlainText s]]
handleCodeBlock _ = CodeBlock []

wrapStringInParagraph :: JsonValue -> Content
wrapStringInParagraph (JsonString s) = Paragraph [PlainText s]
wrapStringInParagraph value = jsonValueToContent value

handleList :: JsonValue -> Content
handleList (JsonArray items) = List (map makeItem items)
    where makeItem = makeListItem
handleList _ = List []

handleParagraph :: [JsonValue] -> Content
handleParagraph values = Paragraph (map jsonValueToContent values)

handlePlainContent :: JsonValue -> Content
handlePlainContent (JsonString s) = PlainText s
handlePlainContent (JsonArray values) = handleParagraph values
handlePlainContent (JsonObject pairs) = handleJsonObject pairs
handlePlainContent _ = PlainText ""

normalizeKeys :: [(String, JsonValue)] -> [(String, JsonValue)]
normalizeKeys = map (\(k, v) -> (trim k, v))

extractStringValue :: [(String, JsonValue)] -> String -> String -> String
extractStringValue pairs key defaultValue =
    maybe defaultValue extractStringContent $ lookup key (normalizeKeys pairs)

extractOptionalStringValue :: [(String, JsonValue)] -> String -> Maybe String
extractOptionalStringValue pairs key =
    fmap extractStringContent $ lookup key (normalizeKeys pairs)

jsonValueToContent :: JsonValue -> Content
jsonValueToContent = jsonValueToContent' 0

trim :: String -> String
trim = f . f
  where f = reverse . dropWhile (== ' ')
