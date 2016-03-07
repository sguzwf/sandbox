CollectDataResult
  { dataTypeToShape = fromList
      [ ( UnQual () (Ident () "Pair")
        , DataShape
            { dataLoc = SrcSpanInfo
              { srcInfoSpan = SrcSpan "mySource.hs" 1 1 10 0
              , srcInfoPoints =
                  [ SrcSpan "mySource.hs" 1 11 1 13
                  , SrcSpan "mySource.hs" 1 26 1 31
                  , SrcSpan "mySource.hs" 2 3 2 3
                  , SrcSpan "mySource.hs" 10 1 10 0
                  ]
              }
            , dataName = UnQual () (Ident () "Pair")
            , dataCons = [(UnQual () (Ident () "Pair"),2,fromList [])]
            }
        )
      ]
  , dataConToShape = fromList
      [ ( UnQual () (Ident () "Pair")
        , ( 0
          , DataShape
              { dataLoc = SrcSpanInfo
                { srcInfoSpan = SrcSpan "mySource.hs" 1 1 10 0
                , srcInfoPoints =
                    [ SrcSpan "mySource.hs" 1 11 1 13
                    , SrcSpan "mySource.hs" 1 26 1 31
                    , SrcSpan "mySource.hs" 2 3 2 3
                    , SrcSpan "mySource.hs" 10 1 10 0
                    ]
                }
              , dataName = UnQual () (Ident () "Pair")
              , dataCons = [(UnQual () (Ident () "Pair"),2,fromList [])]
              }
          )
        )
      ]
  , dataError = []
  }
