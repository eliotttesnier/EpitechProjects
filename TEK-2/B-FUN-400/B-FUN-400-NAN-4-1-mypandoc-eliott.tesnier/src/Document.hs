{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- Document
-}

module Document where

data Header = Header String (Maybe String) (Maybe String)
    deriving (Show, Eq)

data Item = Item [Content]
    deriving (Show, Eq)

data Content
    = PlainText String          -- Regular text
    | Bold Content              -- Bold text
    | Italic Content            -- Italic text
    | InLineCode String         -- Inline code
    | Link String String        -- Link (text, url)
    | Image String String       -- Image (alt text, url)
    | Paragraph [Content]       -- Paragraph of content elements
    | Section Int String [Content] -- Section with level, heading and nested content
    | CodeBlock [Content]          -- Code block
    | List [Item]               -- List with items
    deriving (Show, Eq)

data Document = Document
    { docHeader :: Header
    , docContent :: [Content]
    }
    deriving (Show, Eq)

organizeContent :: [Content] -> [Content]
organizeContent contents = organizeByLevel 1 contents []

organizeByLevel :: Int -> [Content] -> [Content] -> [Content]
organizeByLevel _ [] acc = reverse acc
organizeByLevel currentLevel (s@(Section level title subC):cs) acc
    | level == currentLevel =
        let (sameLevel, rest) = span (\c -> case c of
                                        Section l _ _ -> l > currentLevel
                                        _ -> False) cs
            nested = organizeByLevel (currentLevel + 1) (subC ++ sameLevel) []
            newSection = Section level title nested
        in organizeByLevel currentLevel rest (newSection:acc)
    | otherwise =
        organizeByLevel currentLevel cs (s:acc)
organizeByLevel currentLevel (c:cs) acc =
    organizeByLevel currentLevel cs (c:acc)

createStructuredDocument :: Header -> [Content] -> Document
createStructuredDocument header contents =
    Document header (organizeContent contents)
