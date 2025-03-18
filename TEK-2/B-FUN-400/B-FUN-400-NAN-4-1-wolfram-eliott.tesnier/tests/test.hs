{-
-- EPITECH PROJECT, 2025
-- Tests
-- File description:
-- Tests
-}

import Test.Hspec
import System.Exit
import Validator
import Error
import Config
import Rules

main :: IO ()
main = hspec $ do
    describe "Validators" $ do

        -- validateRule --
        describe "Rule validation" $ do
            it "0 Should return just 0" $ do
                validateRule "0" `shouldBe` Just 0
            it "255 Should return just 255" $ do
                validateRule "255" `shouldBe` Just 255
            it "256 Should return nothing" $ do
                validateRule "256" `shouldBe` Nothing
            it "-1 Should return nothing" $ do
                validateRule "-1" `shouldBe` Nothing
            it "a Should return nothing" $ do
                validateRule "a" `shouldBe` Nothing

        -- validateNonNegative --
        describe "Non-negative validation" $ do
            it "0 Should return just 0" $ do
                validateNonNegative "0" `shouldBe` Just 0
            it "42 Should return just 42" $ do
                validateNonNegative "42" `shouldBe` Just 42
            it "-1 Should return nothing" $ do
                validateNonNegative "-1" `shouldBe` Nothing
            it "a Should return nothing" $ do
                validateNonNegative "a" `shouldBe` Nothing

        -- validatePositive --
        describe "Positive validation" $ do
            it "1 Should return just 1" $ do
                validatePositive "1" `shouldBe` Just 1
            it "42 Should return just 42" $ do
                validatePositive "42" `shouldBe` Just 42
            it "0 Should return nothing" $ do
                validatePositive "0" `shouldBe` Nothing
            it "-1 Should return nothing" $ do
                validatePositive "-1" `shouldBe` Nothing
            it "a Should return nothing" $ do
                validatePositive "a" `shouldBe` Nothing

    -- Error --
    describe "Error" $ do
        it "handleError should exit with 84" $ do
            handleError "Error" `shouldThrow` (== ExitFailure 84)

    -- Config --
    describe "Config" $ do

        -- Default configuration --
        describe "Default configuration" $ do
            it "Should have expected default values" $ do
                rule defaultConf `shouldBe` Nothing
                start defaultConf `shouldBe` 0
                nbLines defaultConf `shouldBe` Nothing
                window defaultConf `shouldBe` 80
                move defaultConf `shouldBe` 0

        -- Arguments parsing --
        describe "Arguments parsing" $ do
            it "Should parse empty args" $ do
                getOpts defaultConf [] `shouldBe` Just defaultConf

            it "Should parse valid rule" $ do
                getOpts defaultConf ["--rule", "30"] `shouldBe`
                    Just defaultConf { rule = Just 30 }

            it "Should parse valid start" $ do
                getOpts defaultConf ["--start", "5"] `shouldBe`
                    Just defaultConf { start = 5 }

            it "Should parse valid lines" $ do
                getOpts defaultConf ["--lines", "10"] `shouldBe`
                    Just defaultConf { nbLines = Just 10 }

            it "Should parse valid window" $ do
                getOpts defaultConf ["--window", "100"] `shouldBe`
                    Just defaultConf { window = 100 }

            it "Should parse valid move" $ do
                getOpts defaultConf ["--move", "3"] `shouldBe`
                    Just defaultConf { move = 3 }

            it "Should parse multiple valid arguments" $ do
                getOpts defaultConf ["--rule", "30", "--start", "5", "--lines", "10"] `shouldBe`
                    Just defaultConf { rule = Just 30, start = 5, nbLines = Just 10 }

            it "Should reject invalid rule" $ do
                getOpts defaultConf ["--rule", "256"] `shouldBe` Nothing

            it "Should reject invalid start" $ do
                getOpts defaultConf ["--start", "-1"] `shouldBe` Nothing

            it "Should reject invalid lines" $ do
                getOpts defaultConf ["--lines", "-5"] `shouldBe` Nothing

            it "Should reject invalid window" $ do
                getOpts defaultConf ["--window", "0"] `shouldBe` Nothing

            it "Should reject invalid move" $ do
                getOpts defaultConf ["--move", "helo"] `shouldBe` Nothing

            it "Should reject invalid argument names" $ do
                getOpts defaultConf ["--invalid", "30"] `shouldBe` Nothing

            it "Should reject missing argument values" $ do
                getOpts defaultConf ["--rule"] `shouldBe` Nothing

            it "Should reject non-numeric values" $ do
                getOpts defaultConf ["--rule", "abc"] `shouldBe` Nothing

    -- Rules --
    describe "Rules" $ do

        -- Subjet rules --
        describe "subject rules" $ do
            it "Should handle rule 30 patterns correctly" $ (do
                case selectRule 30 of
                    Just f -> do
                        f (True, True, True) `shouldBe` False
                        f (True, True, False) `shouldBe` False
                        f (True, False, True) `shouldBe` False
                        f (True, False, False) `shouldBe` True
                        f (False, True, True) `shouldBe` True
                        f (False, True, False) `shouldBe` True
                        f (False, False, True) `shouldBe` True
                        f (False, False, False) `shouldBe` False
                    Nothing -> expectationFailure "Should return Just for rule 30")

            it "Should handle rule 90 patterns correctly" $ (do
                case selectRule 90 of
                    Just f -> do
                        f (True, True, True) `shouldBe` False
                        f (True, True, False) `shouldBe` True
                        f (True, False, True) `shouldBe` False
                        f (True, False, False) `shouldBe` True
                        f (False, True, True) `shouldBe` True
                        f (False, True, False) `shouldBe` False
                        f (False, False, True) `shouldBe` True
                        f (False, False, False) `shouldBe` False
                    Nothing -> expectationFailure "Should return Just for rule 90")

            it "Should handle rule 110 patterns correctly" $ (do
                case selectRule 110 of
                    Just f -> do
                        f (True, True, True) `shouldBe` False
                        f (True, True, False) `shouldBe` True
                        f (True, False, True) `shouldBe` True
                        f (True, False, False) `shouldBe` False
                        f (False, True, True) `shouldBe` True
                        f (False, True, False) `shouldBe` True
                        f (False, False, True) `shouldBe` True
                        f (False, False, False) `shouldBe` False
                    Nothing -> expectationFailure "Should return Just for rule 110")

        -- selectRule --
        describe "selectRule" $ do
            it "Should handle all valid rules (0-255)" $ do
                case selectRule 0 of
                    Just f -> f (False, False, False) `shouldBe` False
                    Nothing -> expectationFailure "Should return Just for rule 0"
                case selectRule 255 of
                    Just f -> f (True, True, True) `shouldBe` True
                    Nothing -> expectationFailure "Should return Just for rule 255"

            it "Should return Nothing for invalid rules" $ do
                case selectRule (-1) of
                    Just _ -> expectationFailure "Should return Nothing for negative rule"
                    Nothing -> return ()
                case selectRule 256 of
                    Just _ -> expectationFailure "Should return Nothing for rule > 255"
                    Nothing -> return ()

        -- patternToIndex --
        describe "patternToIndex" $ do
            it "Should correctly convert patterns to indices" $ do
                patternToIndex (True, True, True) `shouldBe` 7
                patternToIndex (True, True, False) `shouldBe` 6
                patternToIndex (True, False, True) `shouldBe` 5
                patternToIndex (True, False, False) `shouldBe` 4
                patternToIndex (False, True, True) `shouldBe` 3
                patternToIndex (False, True, False) `shouldBe` 2
                patternToIndex (False, False, True) `shouldBe` 1
                patternToIndex (False, False, False) `shouldBe` 0

        -- makeRule --
        describe "makeRule" $ do
            it "Should create rule functions correctly" $ do
                let rule = makeRule 30
                rule (True, True, True) `shouldBe` False
                rule (True, True, False) `shouldBe` False
                rule (True, False, True) `shouldBe` False
                rule (True, False, False) `shouldBe` True
                rule (False, True, True) `shouldBe` True
                rule (False, True, False) `shouldBe` True
                rule (False, False, True) `shouldBe` True
                rule (False, False, False) `shouldBe` False

                let rule = makeRule 90
                rule (True, True, True) `shouldBe` False
                rule (True, True, False) `shouldBe` True
                rule (True, False, True) `shouldBe` False
                rule (True, False, False) `shouldBe` True
                rule (False, True, True) `shouldBe` True
                rule (False, True, False) `shouldBe` False
                rule (False, False, True) `shouldBe` True
                rule (False, False, False) `shouldBe` False

                let rule = makeRule 110
                rule (True, True, True) `shouldBe` False
                rule (True, True, False) `shouldBe` True
                rule (True, False, True) `shouldBe` True
                rule (True, False, False) `shouldBe` False
                rule (False, True, True) `shouldBe` True
                rule (False, True, False) `shouldBe` True
                rule (False, False, True) `shouldBe` True
                rule (False, False, False) `shouldBe` False
