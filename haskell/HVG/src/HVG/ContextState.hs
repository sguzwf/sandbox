module HVG.ContextState where

import Data.Monoid

import HVG.Type

------------------------------
-- manipulate ContextState
--

setTransform :: Matrix -> Builder ()
setTransform val = Builder $ \bld ctx -> (bld, ctx {ctxTransform = val}, ())
getTransform :: Builder Matrix
-- # I know that `ctxTransform ctx` works like `ctx.ctxTransform` in OOPL
-- # so `ctx {ctxTransform = val}` must be the setter or sth..
getTransform = Builder $ \bld ctx -> (bld, ctx, ctxTransform ctx)
applyTransform :: Matrix -> Builder ()
applyTransform val = Builder $ \bld ctx -> (bld, ctx {ctxTransform = val <> ctxTransform ctx}, ())


setFill :: Maybe String -> Builder ()
setFill val = Builder $ \bld ctx -> (bld, ctx {ctxFill = val}, ())
getFill :: Builder (Maybe String)
getFill = Builder $ \bld ctx -> (bld, ctx, ctxFill ctx)

setStroke :: Maybe String -> Builder ()
setStroke val = Builder $ \bld ctx -> (bld, ctx {ctxStroke = val}, ())
getStroke :: Builder (Maybe String)
getStroke = Builder $ \bld ctx -> (bld, ctx, ctxStroke ctx)


setLineWidth :: Double -> Builder ()
setLineWidth val = Builder $ \bld ctx -> (bld, ctx {ctxLineWidth = val}, ())
getLineWidth :: Builder Double
getLineWidth = Builder $ \bld ctx -> (bld, ctx, ctxLineWidth ctx)

setLineCap :: LineCap -> Builder ()
setLineCap val = Builder $ \bld ctx -> (bld, ctx {ctxLineCap = val}, ())
getLineCap :: Builder LineCap
getLineCap = Builder $ \bld ctx -> (bld, ctx, ctxLineCap ctx)

setLineJoin :: LineJoin -> Builder ()
setLineJoin val = Builder $ \bld ctx -> (bld, ctx {ctxLineJoin = val}, ())
getLineJoin :: Builder LineJoin
getLineJoin = Builder $ \bld ctx -> (bld, ctx, ctxLineJoin ctx)

setMiterLimit :: Double -> Builder ()
setMiterLimit val = Builder $ \bld ctx -> (bld, ctx {ctxMiterLimit = val}, ())
getMiterLimit :: Builder Double
getMiterLimit = Builder $ \bld ctx -> (bld, ctx, ctxMiterLimit ctx)

setLineDash :: [Double] -> Builder ()
setLineDash val = Builder $ \bld ctx -> (bld, ctx {ctxLineDash = val}, ())
getLineDash :: Builder [Double]
getLineDash = Builder $ \bld ctx -> (bld, ctx, ctxLineDash ctx)

setLineDashOffset :: Double -> Builder ()
setLineDashOffset val = Builder $ \bld ctx -> (bld, ctx {ctxLineDashOffset = val}, ())
getLineDashOffset :: Builder Double
getLineDashOffset = Builder $ \bld ctx -> (bld, ctx, ctxLineDashOffset ctx)


setTextAlign :: TextAlign -> Builder ()
setTextAlign val = Builder $ \bld ctx -> (bld, ctx {ctxTextAlign = val}, ())
getTextAlign :: Builder TextAlign
getTextAlign = Builder $ \bld ctx -> (bld, ctx, ctxTextAlign ctx)

setTextBaseline :: TextBaseline -> Builder ()
setTextBaseline val = Builder $ \bld ctx -> (bld, ctx {ctxTextBaseline = val}, ())
getTextBaseline :: Builder TextBaseline
getTextBaseline = Builder $ \bld ctx -> (bld, ctx, ctxTextBaseline ctx)

setFont :: String -> Builder ()
setFont val = Builder $ \bld ctx -> (bld, ctx {ctxFont = val}, ())
getFont :: Builder String
getFont = Builder $ \bld ctx -> (bld, ctx, ctxFont ctx)

