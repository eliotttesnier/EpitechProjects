{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-mypandoc-eliott.tesnier
-- File description:
-- test
-}

import Test.Hspec
import ParsingCLISpec
import ParsingJSONSpec
import ParsingXMLSpec
import PrinterMDSpec
import PrinterXMLSpec

main :: IO ()
main = hspec $ do
    describe "ParsingCLI Tests" ParsingCLISpec.spec
    describe "ParsingJSON Tests" ParsingJSONSpec.spec
    describe "ParsingXML Tests" ParsingXMLSpec.spec
    describe "PrinterMD Tests" PrinterMDSpec.spec
    describe "PrinterXML Tests" PrinterXMLSpec.spec
