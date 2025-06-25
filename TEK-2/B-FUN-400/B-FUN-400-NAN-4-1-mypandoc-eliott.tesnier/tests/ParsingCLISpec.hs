{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- ParsingCLISpec
-}

module ParsingCLISpec (spec) where

import Test.Hspec
import ParsingCLI
import System.Directory (doesFileExist, createDirectory, removeFile, doesDirectoryExist)
import System.FilePath ((</>))
import Control.Exception (try, SomeException)
import System.IO (writeFile)
import qualified Parser.Parser as Parser
import Data.Maybe (isJust)

setupTestEnv :: IO ()
setupTestEnv = do
    dirExists <- doesDirectoryExist "test_files"
    if not dirExists
        then createDirectory "test_files"
        else return ()

    writeFile ("test_files" </> "test.json") "{}"
    writeFile ("test_files" </> "test.xml") "<document></document>"
    writeFile ("test_files" </> "test.md") "# Test"

cleanupTestEnv :: IO ()
cleanupTestEnv = do
    let testFiles = ["test.json", "test.xml", "test.md"]
    mapM_ (\f -> do
        fileExists <- doesFileExist ("test_files" </> f)
        if fileExists
            then removeFile ("test_files" </> f)
            else return ()
        ) testFiles

spec :: Spec
spec = beforeAll_ setupTestEnv $ afterAll_ cleanupTestEnv $ do
    describe "isValidFormat" $ do
        it "should recognize xml as valid format" $ do
            isValidFormat "xml" `shouldBe` True

        it "should recognize json as valid format" $ do
            isValidFormat "json" `shouldBe` True

        it "should recognize markdown as valid format" $ do
            isValidFormat "markdown" `shouldBe` True

        it "should reject empty string as invalid format" $ do
            isValidFormat "" `shouldBe` False

        it "should reject unknown formats" $ do
            isValidFormat "html" `shouldBe` False
            isValidFormat "txt" `shouldBe` False
            isValidFormat "pdf" `shouldBe` False

        it "should be case sensitive" $ do
            isValidFormat "XML" `shouldBe` False
            isValidFormat "Json" `shouldBe` False
            isValidFormat "MARKDOWN" `shouldBe` False

    describe "extractPairs" $ do
        it "should extract key-value pairs from command line arguments" $ do
            extractPairs ["-i", "file.json", "-f", "markdown"] `shouldBe`
                [("-i", "file.json"), ("-f", "markdown")]

        it "should ignore unrecognized flags" $ do
            extractPairs ["-x", "unknown", "-i", "file.json"] `shouldBe`
                [("-i", "file.json")]

        it "should handle empty input" $ do
            extractPairs [] `shouldBe` []

        it "should ignore a flag with no value" $ do
            extractPairs ["-i"] `shouldBe` []

        it "should extract all recognized flags" $ do
            extractPairs ["-i", "file.json", "-f", "markdown", "-o", "out.md", "-e", "json"] `shouldBe`
                [("-i", "file.json"), ("-f", "markdown"), ("-o", "out.md"), ("-e", "json")]

        it "should handle flags in any order" $ do
            extractPairs ["-f", "markdown", "-i", "file.json"] `shouldBe`
                [("-f", "markdown"), ("-i", "file.json")]

            extractPairs ["-o", "out.md", "-e", "json", "-i", "file.json", "-f", "markdown"] `shouldBe`
                [("-o", "out.md"), ("-e", "json"), ("-i", "file.json"), ("-f", "markdown")]

        it "should handle duplicate flags (keeping the first occurrence)" $ do
            extractPairs ["-i", "file1.json", "-i", "file2.json"] `shouldBe`
                [("-i", "file1.json"), ("-i", "file2.json")]

        it "should handle values that look like flags" $ do
            extractPairs ["-i", "-f", "-f", "markdown"] `shouldBe`
                [("-i", "-f"), ("-f", "markdown")]

    describe "validateFormat" $ do
        it "should not throw exceptions for valid formats" $ do
            result <- try (validateFormat "markdown" False) :: IO (Either SomeException ())
            case result of
                Left _ -> expectationFailure "Should not have thrown an exception"
                Right _ -> return ()

    describe "validateOutputFile" $ do
        it "should not throw exceptions for Nothing" $ do
            result <- try (validateOutputFile Nothing) :: IO (Either SomeException ())
            case result of
                Left _ -> expectationFailure "Should not have thrown an exception"
                Right _ -> return ()

    describe "validateInputFormat" $ do
        it "should not throw exceptions for Nothing" $ do
            result <- try (validateInputFormat Nothing) :: IO (Either SomeException ())
            case result of
                Left _ -> expectationFailure "Should not have thrown an exception"
                Right _ -> return ()

        it "should not throw exceptions for valid formats" $ do
            result <- try (validateInputFormat (Just "markdown")) :: IO (Either SomeException ())
            case result of
                Left _ -> expectationFailure "Should not have thrown an exception"
                Right _ -> return ()

    describe "parseDocument with optional -e flag" $ do
        it "should parse JSON when -e is not provided and content is JSON" $ do
            let content = "{}"
            Parser.parseDocument "test.json" content "" `shouldSatisfy` isJust

        it "should parse XML when -e is not provided and content is XML" $ do
            let content = "<document></document>"
            Parser.parseDocument "test.xml" content "" `shouldSatisfy` isJust

        it "should fail when -e is not provided and content is neither JSON nor XML" $ do
            let content = "# Invalid"
            Parser.parseDocument "test.md" content "" `shouldBe` Nothing
