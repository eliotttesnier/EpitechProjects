{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- ParserGlobal
-}

module Parser.ParserGlobal
    ( Parser(..)
    , parseChar
    , parseAnyChar
    , parseString
    , parseIf
    , parseMany
    , parseSome
    , parseUInt
    , parseDouble
    , parseInt
    , parseSpace
    , parseSpaces
    , token
    ) where

import Data.Char (isDigit, isSpace)
import Control.Applicative (Alternative(..))

data Parser a = Parser {
  runParser :: String -> Maybe (a, String)
}

parseChar :: Char -> Parser Char
parseChar c = Parser $ \input ->
  case input of
    (x:xs) | x == c -> Just (x, xs)
    _               -> Nothing

parseAnyChar :: String -> Parser Char
parseAnyChar [] = Parser $ \_ -> Nothing
parseAnyChar (c:cs) = parseChar c <|> parseAnyChar cs

parseString :: String -> Parser String
parseString s = parseString' s
  where
    parseString' [] = return []
    parseString' (x:xs) = do
      y <- parseChar x
      ys <- parseString' xs
      return (y:ys)

parseIf :: (Char -> Bool) -> Parser Char
parseIf cond = Parser $ \input ->
  case input of
    (c:cs) | cond c -> Just (c, cs)
    _               -> Nothing

parseMany :: Parser a -> Parser [a]
parseMany parser = parseMany1 parser <|> pure []
  where
    parseMany1 p = do
      x <- p
      xs <- parseMany p
      return (x:xs)

parseSome :: Parser a -> Parser [a]
parseSome p = do
  x <- p
  xs <- parseMany p
  return (x:xs)

parseUInt :: Parser Int
parseUInt = do
  digits <- parseSome (parseIf isDigit)
  return (read digits)

parseFractionalPart :: Parser Double
parseFractionalPart = do
    _ <- parseChar '.'
    digits <- parseSome (parseIf isDigit)
    let n = length digits
    let value = read digits :: Int
    return (fromIntegral value / 10^n)

parseDouble :: Parser Double
parseDouble = do
    intPart <- parseUInt
    fracPart <- parseFractionalPart <|> return 0
    return (fromIntegral intPart + fracPart)

parseInt :: Parser Int
parseInt = do
  sign <- parseChar '-' <|> return '+'
  n <- parseUInt
  return (if sign == '-' then -n else n)

parseSpace :: Parser Char
parseSpace = parseIf isSpace

parseSpaces :: Parser String
parseSpaces = parseMany parseSpace

token :: Parser a -> Parser a
token p = do
  _ <- parseSpaces
  x <- p
  _ <- parseSpaces
  return x

instance Functor Parser where
  fmap f (Parser p) = Parser $ \input ->
    case p input of
      Nothing -> Nothing
      Just (x, rest) -> Just (f x, rest)

instance Applicative Parser where
  pure x = Parser $ \input -> Just (x, input)
  (Parser pf) <*> (Parser px) = Parser $ \input ->
    case pf input of
      Nothing -> Nothing
      Just (f, rest1) ->
        case px rest1 of
          Nothing -> Nothing
          Just (x, rest2) -> Just (f x, rest2)

instance Alternative Parser where
  empty = Parser $ \_ -> Nothing
  (Parser p1) <|> (Parser p2) = Parser $ \input ->
    case p1 input of
      Nothing -> p2 input
      success -> success

instance Monad Parser where
  return = pure
  (Parser p) >>= f = Parser $ \input ->
    case p input of
      Nothing -> Nothing
      Just (x, rest) -> runParser (f x) rest


