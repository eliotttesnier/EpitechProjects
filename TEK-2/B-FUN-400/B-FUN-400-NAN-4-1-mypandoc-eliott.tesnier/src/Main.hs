{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- Main
-}

module Main (main) where

import ParsingCLI
import System.Exit (exitSuccess, exitWith, ExitCode(..))
import Control.Exception (try, SomeException)
import qualified Parser.Parser as Parser
import qualified Printers.MarkdownPrinter as MarkdownPrinter
import qualified Printers.XmlPrinter as XmlPrinter
import qualified Printers.JsonPrinter as JsonPrinter
import Document
import Data.Maybe (fromMaybe)

convertDocument :: Options -> Document -> String
convertDocument opts doc =
    case optOutputFormat opts of
        "markdown" -> MarkdownPrinter.printMarkdown doc
        "xml"   -> XmlPrinter.printXml doc
        "json"  -> JsonPrinter.printJson doc
        _ -> show doc

handleParsingError :: String -> IO a
handleParsingError msg = putStrLn msg >> exitWith (ExitFailure 84)

processDocument :: Options -> Document -> IO ()
processDocument opts doc = putStr (convertDocument opts doc) >> exitSuccess

determineInputFormat :: Options -> String -> String
determineInputFormat opts content =
    case optInputFormat opts of
        Just format -> format
        Nothing     -> Parser.detectFormat content

processFormatConversion :: Options -> String -> String -> IO ()
processFormatConversion opts content inputFormat =
    case Parser.parseDocument (optInputFile opts) content inputFormat of
        Nothing -> handleParsingError "Error: Failed to parse document"
        Just doc ->
            case optOutputFile opts of
                Nothing -> processDocument opts doc
                Just outputFile -> writeFile outputFile
                    (convertDocument opts doc) >> exitSuccess

handleOptions :: Options -> IO ()
handleOptions opts = do
    content <- readFile (optInputFile opts)
    let inputFormat = determineInputFormat opts content
    if inputFormat == optOutputFormat opts && inputFormat /= ""
    then
        case optOutputFile opts of
            Nothing -> putStr content >> exitSuccess
            Just outputFile -> writeFile outputFile content >> exitSuccess
    else processFormatConversion opts content inputFormat

main :: IO ()
main = do
    result <- try parseArgs :: IO (Either SomeException Options)
    case result of
        Left e -> handleParsingError ("Error: " ++ show e)
        Right opts -> handleOptions opts
