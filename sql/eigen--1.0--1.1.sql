--------- ARRAYXI ADDITIONAL SIMILARITY METRIC -------

CREATE OR REPLACE FUNCTION arrayxi_tanimoto(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_tanimoto(arrayxi, arrayxi) IS
    'Returns the Tanimoto similarity between the arrays.';

    
--------- ARRAYXI NON-BINARY/QUANTITATIVE METRICS -------

CREATE OR REPLACE FUNCTION arrayxi_tanimoto_nb(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_tanimoto_nb(arrayxi, arrayxi) IS
    'Returns the non-binary Tanimoto similarity between the arrays.';
    

CREATE OR REPLACE FUNCTION arrayxi_dice_nb(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_dice_nb(arrayxi, arrayxi) IS
    'Returns the non-binary Dice similarity between the arrays.';
    
    
CREATE OR REPLACE FUNCTION arrayxi_cosine_nb(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_cosine_nb(arrayxi, arrayxi) IS
    'Returns the non-binary Cosine similarity between the arrays.';
    
    
---- Limit checking/setting functions -----

CREATE OR REPLACE FUNCTION show_arrayxi_similarity_limit(metric text)
    RETURNS float4
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION show_arrayxi_similarity_limit(metric text) IS
    'Show the current similarity limit (or Tversky factor) for a given metric.
    Valid values: euclidean, kulczynski, manhattan, ochiai, rusell-rao, simpson,
    tanimoto, tversky, tversky_alpha, tversky_beta.';


CREATE OR REPLACE FUNCTION set_arrayxi_similarity_limit(sim_limit float4, metric text)
    RETURNS float4
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION set_arrayxi_similarity_limit(sim_limit float4, metric text) IS
    'Set the similarity limit (or Tversky factor) for a given metric.
    Valid values: euclidean, kulczynski, manhattan, ochiai, rusell-rao, simpson,
    tanimoto, tversky, tversky_alpha, tversky_beta.';

    
----ARRAYXI BOOLEAN METRICS: COMPARES THE SIMILARITY WITH THE USER-SET LIMIT----
-----------------REQUIRED FOR POSTGRESQL GIST INDEX ON ARRAYXI------------------


CREATE OR REPLACE FUNCTION arrayxi_tanimoto_is_above_limit(arrayxi, arrayxi)
    RETURNS BOOLEAN
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_tanimoto_is_above_limit(arrayxi, arrayxi) IS
    'Returns true if the Tanimoto similarity between two arrays is above the user-set limit.';


