{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- parsingCLI
-}

module ParsingCLI
    ( Options(..)
    , parseArgs
    , isValidFormat
    , extractPairs
    , validateFormat
    , validateOutputFile
    , validateInputFormat
    , validateInputFile
    ) where

import System.Environment (getArgs)
import System.Exit (exitWith, ExitCode(..))
import System.IO (hPutStrLn, stderr)
import Control.Monad (when)
import Control.Exception (try, SomeException)

data Options = Options
    { optInputFile    :: FilePath
    , optOutputFormat :: String
    , optOutputFile   :: Maybe FilePath
    , optInputFormat  :: Maybe String
    } deriving (Show)

data ValidationError
    = FileNotFound FilePath
    | InvalidOutputFormat String
    | InvalidInputFormat String
    | MissingRequiredArg String
    deriving (Show)

usage :: IO ()
usage = hPutStrLn stderr $ unlines
    [ "USAGE: ./mypandoc -i ifile -f oformat [-o ofile] [-e iformat]\n"
    , "\tifile       path to the file to convert"
    , "\toformat     output format (xml, json, markdown)"
    , "\tofile       path to the output file"
    , "\tiformat     input format (xml, json, markdown)"
    ]

errorMessage :: ValidationError -> String
errorMessage (FileNotFound path) =
    "File not found: " ++ path
errorMessage (InvalidOutputFormat fmt) =
    "Invalid output format: " ++ fmt ++ " (must be xml, json, or markdown)"
errorMessage (InvalidInputFormat fmt) =
    "Invalid input format: " ++ fmt ++ " (must be xml, json, or markdown)"
errorMessage (MissingRequiredArg arg) =
    "Missing required argument: " ++ arg

handleError :: ValidationError -> IO a
handleError err =
    usage >>
    hPutStrLn stderr ("Error: " ++ errorMessage err) >>
    exitWith (ExitFailure 84)

isValidFormat :: String -> Bool
isValidFormat fmt = fmt `elem` ["xml", "json", "markdown", "debug"]

getRequiredArg :: String -> [(String, String)] -> IO String
getRequiredArg flag pairs =
    maybe (handleError $ MissingRequiredArg flag) return $ lookup flag pairs

validateInputFile :: FilePath -> IO ()
validateInputFile path = do
    result <- try (readFile path) :: IO (Either SomeException String)
    case result of
        Left _ -> handleError $ FileNotFound path
        Right _ -> return ()

validateOutputFile :: Maybe FilePath -> IO ()
validateOutputFile Nothing = return ()
validateOutputFile (Just _) = return ()

validateFormat :: String -> Bool -> IO ()
validateFormat fmt isInput =
    when (not $ isValidFormat fmt) $
        handleError $ if isInput then InvalidInputFormat fmt
                      else InvalidOutputFormat fmt

validateInputFormat :: Maybe String -> IO ()
validateInputFormat Nothing = return ()
validateInputFormat (Just fmt) = validateFormat fmt True

parseOptions :: [(String, String)] -> IO Options
parseOptions pairs = do
    inputFile <- getRequiredArg "-i" pairs
    outputFormat <- getRequiredArg "-f" pairs
    let outputFile = lookup "-o" pairs
    let inputFormat = lookup "-e" pairs
    validateInputFile inputFile
    validateFormat outputFormat False
    validateOutputFile outputFile
    validateInputFormat inputFormat
    return $ Options inputFile outputFormat outputFile inputFormat

extractPairs :: [String] -> [(String, String)]
extractPairs [] = []
extractPairs [_] = []
extractPairs (flag:value:rest)
    | isFlag flag = (flag, value) : extractPairs rest
    | otherwise   = extractPairs (value:rest)
  where
    isFlag s = s `elem` ["-i", "-f", "-o", "-e"]

handleEmptyArgs :: IO a
handleEmptyArgs = usage >> exitWith (ExitFailure 84)

parseArgs :: IO Options
parseArgs = do
    args <- getArgs
    case args of
        [] -> handleEmptyArgs
        _  -> let pairs = extractPairs args
              in if null pairs
                 then handleEmptyArgs
                 else parseOptions pairs
