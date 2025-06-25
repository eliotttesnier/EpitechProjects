{-
-- EPITECH PROJECT, 2025
-- imageCompressor
-- File description:
-- Clustering
-}

module Clustering where

import FileParsing
import Distance
import Config
import Control.Parallel.Strategies
import Data.List ( minimumBy )
import Data.Function ( on )
import qualified Data.Map.Strict as Map
import qualified Data.Set as Set

data Cluster = Cluster {
    _centroid :: Color,
    _meanCentroid :: Color,
    _pixels :: Set.Set CustomPixel
} deriving (Eq, Ord)

instance Show Cluster where
    show (Cluster _ mean pixels) =
        "--\n" ++ show mean ++ "\n-\n" ++ unlines (map show (Set.toList pixels))

findClosestCluster :: Color -> [Cluster] -> Color
findClosestCluster color = _centroid .
    minimumBy (compare `on` (distance color . _centroid))

addColors :: Color -> Color -> Color
addColors (r1, g1, b1) (r2, g2, b2) = (r1 + r2, g1 + g2, b1 + b2)

clusterPixels :: [CustomPixel] -> [Cluster] -> [Cluster]
clusterPixels [] clusters = clusters
clusterPixels pxls clusters =
    let pixelAssignments = withStrategy (parList rseq) $ map
            (\p -> let closest = findClosestCluster (_color p) clusters in
            (closest, (addColors (_color p) (0, 0, 0), Set.singleton p))) pxls
        mergedClusters = Map.fromListWith (\(c1, pxs1) (c2, pxs2) ->
            (addColors c1 c2, Set.union pxs1 pxs2)) pixelAssignments
    in withStrategy (parList rseq) $ map
        (\(cent, (sumColor, pxs)) -> Cluster cent sumColor pxs)
        (Map.toList mergedClusters)

getMeanCentroid :: Cluster -> Cluster
getMeanCentroid cluster@(Cluster {_meanCentroid = (r, g, b), _pixels = pxs}) =
    let toDouble x = fromIntegral x :: Double
        nbPx = max 1 (toDouble (Set.size pxs))
    in cluster {_meanCentroid = (round (toDouble r / nbPx),
                                 round (toDouble g / nbPx),
                                 round (toDouble b / nbPx))}

resetClusters :: [Cluster] -> [Cluster]
resetClusters = parMap rseq (\c -> Cluster (_meanCentroid c) (0,0,0) Set.empty)

areClustersFarFromMean :: Config -> [Cluster] -> Bool
areClustersFarFromMean (Config {_convergence = conv})=
    any (\c -> distance (_centroid c) (_meanCentroid c) >= conv)

calculateClusters :: Config -> [CustomPixel] -> [Cluster] -> [Cluster]
calculateClusters conf pixels lastClusters =
    let clustered = clusterPixels pixels lastClusters
        meanCentroids = map getMeanCentroid clustered
    in if areClustersFarFromMean conf meanCentroids
        then calculateClusters conf pixels (resetClusters meanCentroids)
        else meanCentroids
