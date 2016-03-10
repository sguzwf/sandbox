module Paths_zoomcraft (
    version,
    getBinDir, getLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
catchIO = Exception.catch

version :: Version
version = Version [0,1,0,0] []
bindir, libdir, datadir, libexecdir, sysconfdir :: FilePath

bindir     = "/Users/caasi/Documents/sandbox/haskell/zoom/.cabal-sandbox/bin"
libdir     = "/Users/caasi/Documents/sandbox/haskell/zoom/.cabal-sandbox/lib/x86_64-osx-ghc-7.10.2/zoomcraft-0.1.0.0-I0EKir9PGbyBOpYbjKBZpM"
datadir    = "/Users/caasi/Documents/sandbox/haskell/zoom/.cabal-sandbox/share/x86_64-osx-ghc-7.10.2/zoomcraft-0.1.0.0"
libexecdir = "/Users/caasi/Documents/sandbox/haskell/zoom/.cabal-sandbox/libexec"
sysconfdir = "/Users/caasi/Documents/sandbox/haskell/zoom/.cabal-sandbox/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "zoomcraft_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "zoomcraft_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "zoomcraft_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "zoomcraft_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "zoomcraft_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
