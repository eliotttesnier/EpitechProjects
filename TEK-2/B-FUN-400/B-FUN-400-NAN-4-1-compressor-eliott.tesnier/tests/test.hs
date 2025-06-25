{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-compressor-eliott.tesnier
-- File description:
-- test
-}

import Test.Hspec
import Validators
import Config
import FileParsing
import Distance
import Centroids
import Clustering

import qualified Data.Set as Set

main :: IO ()
main = hspec $ do
    describe "Validators" $ do
        describe "validateNbColor" $ do
            it "returns Nothing for negative numbers" $ do
                validateNbColor "-5" `shouldBe` Nothing

            it "returns Nothing for zero" $ do
                validateNbColor "0" `shouldBe` Nothing

            it "returns Nothing for non-numeric input" $ do
                validateNbColor "abc" `shouldBe` Nothing

            it "returns Nothing for float numbers" $ do
                validateNbColor "0.5" `shouldBe` Nothing

            it "returns Just n for positive numbers" $ do
                validateNbColor "8" `shouldBe` Just 8

        describe "validateConvergence" $ do
            it "returns Nothing for negative numbers" $ do
                validateConvergence "-0.5" `shouldBe` Nothing

            it "returns Nothing for zero" $ do
                validateConvergence "0" `shouldBe` Nothing

            it "returns Nothing for non-numeric input" $ do
                validateConvergence "abc" `shouldBe` Nothing

            it "returns Just n for positive numbers" $ do
                validateConvergence "0.2" `shouldBe` Just 0.2

    describe "Config" $ do
        describe "parseArgs" $ do
            it "returns emptyConfig for no arguments" $ do
                parseArgs emptyConfig [] `shouldBe` Just emptyConfig

            it "return partially empty for not all arguments" $ do
                parseArgs emptyConfig ["-n", "8", "-l", "0.2"] `shouldBe` Just (ParseConfig (Just 8) (Just 0.2) Nothing)

            it "returns Nothing for unknown arguments" $ do
                parseArgs emptyConfig ["-n", "8", "-l", "0.2", "-f", "in", "-z"] `shouldBe` Nothing

            it "returns Nothing for incomplete arguments" $ do
                parseArgs emptyConfig ["-n", "8", "-l", "0.2"] `shouldBe`
                    Just (ParseConfig (Just 8) (Just 0.2) Nothing)

            it "returns Nothing for baddly formated -n (No data)" $ do
                parseArgs emptyConfig ["-n", "-l", "0.2", "-f", "in"] `shouldBe` Nothing

            it "returns Nothing for badly formatted -n (Alphabetic data)" $ do
                parseArgs emptyConfig ["-n", "abc", "-l", "0.2", "-f", "in"] `shouldBe` Nothing

            it "returns Nothing for badly formatted -n (Zero data)" $ do
                parseArgs emptyConfig ["-n", "0", "-l", "0.2", "-f", "in"] `shouldBe` Nothing

            it "returns Nothing for badly formatted -n (Float data)" $ do
                parseArgs emptyConfig ["-n", "0.5", "-l", "0.2", "-f", "in"] `shouldBe` Nothing

            it "returns Nothing for badly formatted -l (No data)" $ do
                parseArgs emptyConfig ["-n", "8", "-l", "-f", "in"] `shouldBe` Nothing

            it "returns Nothing for badly formatted -l (Alphabetic data)" $ do
                parseArgs emptyConfig ["-n", "8", "-l", "abc", "-f", "in"] `shouldBe` Nothing

            it "returns Nothing for badly formatted -l (Negative data)" $ do
                parseArgs emptyConfig ["-n", "8", "-l", "-5", "-f", "in"] `shouldBe` Nothing

            it "returns Nothing for badly formatted -l (Zero data)" $ do
                parseArgs emptyConfig ["-n", "8", "-l", "0", "-f", "in"] `shouldBe` Nothing

            it "returns Nothing for badly formatted -f (No data)" $ do
                parseArgs emptyConfig ["-n", "8", "-l", "0.2", "-f"] `shouldBe` Nothing

        describe "getOpts" $ do
            it "returns Nothing for invalid arguments" $ do
                getOpts ["-n", "-5", "-l", "0.2", "-f", "in"] `shouldBe` Nothing

            it "returns Just Config for valid arguments" $ do
                getOpts ["-n", "8", "-l", "0.2", "-f", "in"] `shouldBe`
                    Just (Config 8 0.2 "in")

    describe "Parsing" $ do
        describe "parseLine" $ do
            it "returns Nothing for empty list" $ do
                parseLine [] `shouldBe` Nothing

            it "returns Nothing for list with one element" $ do
                parseLine ["(1,2)"] `shouldBe` Nothing

            it "returns Nothing for badly formatted first element" $ do
                parseLine ["(a,2)", "(3,4,5)"] `shouldBe` Nothing

            it "returns Nothing for badly formatted second element" $ do
                parseLine ["(1,2)", "(3,4,a)"] `shouldBe` Nothing

            it "returns Nothing for a list with more than two elements" $ do
                parseLine ["(1,2)", "(3,4,5)", "(6,7)"] `shouldBe` Nothing

            it "returns Just Pixel for well formatted elements" $ do
                parseLine ["(1,2)", "(3,4,5)"] `shouldBe` Just (Pixel (1, 2) (3, 4, 5))

        describe "parseLines" $ do
            it "returns Just [] for empty list" $ do
                parseLines [] `shouldBe` Just []

            it "returns a list with one pixel for a list with one line" $ do
                parseLines ["(1,2) (3,4,5)"] `shouldBe` Just [Pixel (1, 2) (3, 4, 5)]

            it "returns Nothing for a list with one badly formatted line" $ do
                parseLines ["(1,2) (3,4,a)"] `shouldBe` Nothing

            it "returns a list of pixels for a list with multiple lines" $ do
                parseLines ["(1,2) (3,4,5)", "(6,7) (8,9,10)"] `shouldBe`
                    Just [Pixel (1, 2) (3, 4, 5), Pixel (6, 7) (8, 9, 10)]

        describe "parseFile" $ do
            it "returns Just [] for empty file" $ do
                parseFile "" `shouldBe` Just []

            it "returns a list of pixels for a file with multiple lines" $ do
                parseFile "(1,2) (3,4,5)\n(6,7) (8,9,10)" `shouldBe`
                    Just [Pixel (1, 2) (3, 4, 5), Pixel (6, 7) (8, 9, 10)]

            it "returns Nothing for a file with one badly formatted line" $ do
                parseFile "(1,2) (3,4,5)\n(6,7) (8,9,a)" `shouldBe` Nothing

    describe "Distance" $ do
        it "returns 0 for the same color (0)" $ do
            distance (0, 0, 0) (0, 0, 0) `shouldBe` 0.0

        it "returns 0 for the same color (255)" $ do
            distance (255, 255, 255) (255, 255, 255) `shouldBe` 0.0

        it "returns 441.67... for max distance (black to white)" $ do
            distance (0, 0, 0) (255, 255, 255) `shouldBe` 441.6729559300637

        it "returns 441.67... for max distance (white to black)" $ do
            distance (255, 255, 255) (0, 0, 0) `shouldBe` 441.6729559300637

        it "returns 375.85... for distance (15 to 232)" $ do
            distance (15, 15, 15) (232, 232, 232) `shouldBe` 375.85502524244635

    describe "Centroids" $ do
        let testPixels = [
                Pixel (0, 0) (0, 0, 0),
                Pixel (0, 0) (255, 255, 255),
                Pixel (0, 0) (128, 128, 128),
                Pixel (0, 0) (64, 64, 64)]

        describe "generateIndices" $ do
            it "generates correct number of indices" $ do
                length (generateIndices 42 3 4) `shouldBe` 3

            it "generates indices within bounds" $ do
                all (< 4) (generateIndices 42 3 4) `shouldBe` True
                all (>= 0) (generateIndices 42 3 4) `shouldBe` True

            it "generates same sequence for same seed" $ do
                generateIndices 42 3 4 `shouldBe` generateIndices 42 3 4

            it "generates different sequence for different seed" $ do
                generateIndices 42 3 4 `shouldNotBe` generateIndices 43 3 4

        describe "initializeCentroids" $ do
            it "returns correct number of centroids" $ do
                length (initializeCentroids 2 testPixels) `shouldBe` 2

            it "returns centroids from input pixels" $ do
                let centroids = initializeCentroids 2 testPixels
                all (`elem` map _color testPixels) centroids `shouldBe` True

            it "returns same centroids for same input" $ do
                initializeCentroids 2 testPixels `shouldBe` initializeCentroids 2 testPixels

            it "handles k equal to number of pixels" $ do
                length (initializeCentroids 4 testPixels) `shouldBe` 4

    describe "Clustering" $ do
        let testPixels = [
                Pixel (0, 0) (33, 18, 109),
                Pixel (0, 1) (33, 18, 109),
                Pixel (0, 2) (33, 21, 109),
                Pixel (0, 3) (33, 21, 112),
                Pixel (0, 4) (33, 25, 112),
                Pixel (0, 5) (33, 32, 112),
                Pixel (1, 0) (33, 18, 109),
                Pixel (1, 1) (35, 18, 109),
                Pixel (1, 2) (35, 21, 109),
                Pixel (1, 3) (38, 21, 112)]
        
        describe "clusterPixels" $ do
            it "returns correct number of clusters" $ do
                length (clusterPixels testPixels (map (\x -> Cluster x (0,0,0) Set.empty) (initializeCentroids 2 testPixels))) `shouldBe` 2

            it "returns correct clusters" $ do
                let baseClusters = [
                        Cluster (33, 18, 109) (0, 0, 0) Set.empty,
                        Cluster (35, 21, 109) (0, 0, 0) Set.empty]
                let resultClusters = [
                        Cluster (33, 18, 109) (134, 72, 436) (Set.fromList [
                            Pixel (1, 1) (35, 18, 109),
                            Pixel (1, 0) (33, 18, 109),
                            Pixel (0, 1) (33, 18, 109),
                            Pixel (0, 0) (33, 18, 109)]),
                        Cluster (35, 21, 109) (205, 141, 666) (Set.fromList [
                            Pixel (1, 3) (38, 21, 112),
                            Pixel (1, 2) (35, 21, 109),
                            Pixel (0, 5) (33, 32, 112),
                            Pixel (0, 4) (33, 25, 112),
                            Pixel (0, 3) (33, 21, 112),
                            Pixel (0, 2) (33, 21, 109)])
                            ]
                show (clusterPixels testPixels baseClusters) `shouldBe` show resultClusters
            
            it "get the mean centroid of a cluster" $ do
                let cluster = Cluster (33, 18, 109) (4, 8, 12) (Set.fromList [
                        Pixel (1, 1) (1, 2, 3),
                        Pixel (1, 0) (1, 2, 3),
                        Pixel (0, 1) (1, 2, 3),
                        Pixel (0, 0) (1, 2, 3)])
                getMeanCentroid cluster `shouldBe` Cluster (33, 18, 109) (1, 2, 3) (Set.fromList [
                        Pixel (1, 1) (1, 2, 3),
                        Pixel (1, 0) (1, 2, 3),
                        Pixel (0, 1) (1, 2, 3),
                        Pixel (0, 0) (1, 2, 3)])
            
            it "prepare clusters for next calculations" $ do
                let clusters = [
                        Cluster (33, 18, 109) (35, 21, 109) (Set.fromList [
                            Pixel (1, 1) (35, 18, 109),
                            Pixel (1, 0) (56, 9, 109),
                            Pixel (0, 1) (33, 27, 109),
                            Pixel (0, 0) (10, 18, 109)]),
                        Cluster (33, 18, 109) (35, 21, 109) (Set.fromList [
                            Pixel (1, 3) (38, 21, 112),
                            Pixel (1, 2) (35, 21, 109),
                            Pixel (0, 5) (33, 32, 112),
                            Pixel (0, 4) (33, 25, 112),
                            Pixel (0, 3) (33, 21, 112),
                            Pixel (0, 2) (33, 21, 109)])
                            ]
                resetClusters clusters `shouldBe` [
                    Cluster (35, 21, 109) (0, 0, 0) Set.empty,
                    Cluster (35, 21, 109) (0, 0, 0) Set.empty]
