{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-wolfram-eliott.tesnier
-- File description:
-- Wolfram
-}

module Wolfram where

type RuleFunction = (Char, Char, Char) -> Char
type Line = [Char]

-- Create initial line with center cell active
initLine :: Int -> Line
initLine width =
    let halfWidth = width `div` 2
    in replicate halfWidth ' ' ++ ['*'] ++ replicate halfWidth ' '

-- Get three cells for rule application
getTriple :: Line -> Int -> (Char, Char, Char)
getTriple line 0 = (' ', head line, line !! 1)
getTriple line i
    | i == length line - 1 = (line !! (i-1), line !! i, ' ')
    | otherwise = (line !! (i-1), line !! i, line !! (i+1))

-- Generate next line using rule
nextLine :: RuleFunction -> Line -> Line
nextLine rule line =
    [rule (getTriple line i) | i <- [0..length line - 1]]

-- Generate next generation with growing width
nextGeneration :: RuleFunction -> Line -> Line
nextGeneration rule line =
    ' ' : nextLine rule line ++ [' ']

-- Generate pattern from initial state
generatePattern :: RuleFunction -> Int -> Int -> Maybe Int -> [Line]
generatePattern rule window start mlines =
    let initial = initLine window
        allLines = iterate (nextGeneration rule) initial
        startedLines = drop start allLines
    in case mlines of
        Just n -> take n startedLines
        Nothing -> startedLines

applyPadding :: Int -> String -> String
applyPadding move line
    | move > 0 = replicate move ' ' ++ line
    | move < 0 = drop (abs move) line
    | otherwise = line

-- Run Wolfram automaton
runWolfram :: RuleFunction -> Int -> Int -> Int -> Maybe Int -> IO ()
runWolfram rule window start move mlines =
    let pattern = generatePattern rule window start mlines
        displayLine line =
            let centerOffset = (length line - window) `div` 2
                fullLine = applyPadding move (line)
            in putStrLn . take window . drop centerOffset $ fullLine
    in mapM_ displayLine pattern