--------------------------------------------------------------------------------
---------------------------- SUPPPORT FUNCTIONS --------------------------------
--------------------------------------------------------------------------------



CREATE FUNCTION array_has_nulls(anyarray)
RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION array_has_nulls(anyarray) IS 'Returns true if the array contains a NULL value.';



--------------------------------------------------------------------------------
-------------------- VECTOR3D: THREE-DIMENSIONAL VECTOR ------------------------
--------------------------------------------------------------------------------



CREATE  DOMAIN vector3d AS _float8
        CONSTRAINT onedimensional CHECK(ARRAY_NDIMS(VALUE) = 1)
        CONSTRAINT nonulls CHECK(array_has_nulls(VALUE) = FALSE)
        CONSTRAINT xyz CHECK(array_upper(VALUE,1) = 3);

COMMENT ON DOMAIN vector3d IS
    'three-dimensional vector of double precision floats.';


CREATE  DOMAIN matrixxd AS _float8
        CONSTRAINT twodimensional CHECK(ARRAY_NDIMS(VALUE) <= 2)
        CONSTRAINT nonulls CHECK(array_has_nulls(VALUE) = FALSE);

COMMENT ON TYPE matrixxd IS
    'Two-dimensional matrix of double precision floats. Can be one-dimensional if the matrix has only one row.';
  
    
CREATE  FUNCTION vector3d_constant(value DOUBLE PRECISION)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C VOLATILE STRICT;

COMMENT ON FUNCTION vector3d_constant(DOUBLE PRECISION) IS
    'Returns a vector with constant elements.';


CREATE  FUNCTION vector3d_random()
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C VOLATILE STRICT;

COMMENT ON FUNCTION vector3d_random() IS
    'Returns a vector with random elements.';


CREATE  FUNCTION vector3d_add(vector3d, vector3d)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_add(vector3d, vector3d) IS
    'Adds two vectors together.';


CREATE  OPERATOR + (
        PROCEDURE = vector3d_add,
        LEFTARG = vector3d,
        RIGHTARG = vector3d,
        COMMUTATOR = +);

COMMENT ON OPERATOR +(vector3d, vector3d) IS
    'Adds two vectors together.';


CREATE  FUNCTION vector3d_subtract(vector3d, vector3d)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_subtract(vector3d, vector3d) IS
    'Subtracts one vector from the other.';


CREATE  OPERATOR - (
        PROCEDURE = vector3d_subtract,
        LEFTARG = vector3d,
        RIGHTARG = vector3d);

COMMENT ON OPERATOR -(vector3d, vector3d) IS
    'Subtracts one vector from the other.';


CREATE  FUNCTION vector3d_scalar_division(vector3d, DOUBLE PRECISION)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_scalar_division(vector3d, DOUBLE PRECISION) IS
    'Divides a vector by a scalar.';


CREATE  OPERATOR / (
        PROCEDURE = vector3d_scalar_division,
        LEFTARG = vector3d,
        RIGHTARG = DOUBLE PRECISION);

COMMENT ON OPERATOR /(vector3d, DOUBLE PRECISION) IS
    'Divides a vector by a scalar.';


CREATE  FUNCTION vector3d_scalar_product(vector3d, DOUBLE PRECISION)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_scalar_product(vector3d, DOUBLE PRECISION) IS
    'Multiplication of a vector with scalar.';


CREATE  OPERATOR * (
        PROCEDURE = vector3d_scalar_product,
        LEFTARG = vector3d,
        RIGHTARG = DOUBLE PRECISION);

COMMENT ON OPERATOR *(vector3d, DOUBLE PRECISION) IS
    'Multiplication of a vector with scalar.';


CREATE  FUNCTION vector3d_dot(vector3d, vector3d)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_dot(vector3d, vector3d) IS
    'Dot product between two vectors.';


CREATE  OPERATOR * (
        PROCEDURE = vector3d_dot,
        LEFTARG = vector3d,
        RIGHTARG = vector3d,
        COMMUTATOR = *);

COMMENT ON OPERATOR * (vector3d, vector3d) IS
    'Dot product between two vectors.';


CREATE  FUNCTION vector3d_norm(vector3d)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_norm(vector3d) IS
    'Length/Norm of the vector.';


CREATE  OPERATOR | (
        PROCEDURE = vector3d_norm,
        RIGHTARG = vector3d
        );

COMMENT ON OPERATOR |(NONE, vector3d) IS
    'Length/Norm of the vector.';


CREATE  FUNCTION vector3d_normalized(vector3d)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_normalized(vector3d) IS
    'Normalizes vector.';

CREATE  OPERATOR ^ (
        PROCEDURE = vector3d_normalized,
        RIGHTARG = vector3d
        );

COMMENT ON FUNCTION vector3d_normalized(vector3d) IS
    'Normalizes vector.';


CREATE  FUNCTION vector3d_cross(vector3d, vector3d)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_cross(vector3d, vector3d) IS
    'Cross product between two vectors.';


CREATE  OPERATOR # (
        PROCEDURE = vector3d_cross,
        LEFTARG = vector3d,
        RIGHTARG = vector3d
        );

COMMENT ON OPERATOR #(vector3d, vector3d) IS
    'Cross product between two vectors.';


CREATE  FUNCTION vector3d_distance(vector3d, vector3d)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_distance(vector3d, vector3d) IS
    'Euclidean distance between two vectors.';


CREATE  OPERATOR -> (
        PROCEDURE = vector3d_distance,
        LEFTARG = vector3d,
        RIGHTARG = vector3d
        );

COMMENT ON OPERATOR ->(vector3d, vector3d) IS
    'Euclidean distance between two vectors.';


CREATE  FUNCTION vector3d_angle(vector3d, vector3d)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_angle(vector3d, vector3d) IS
    'Angle between two vectors in radians.';


CREATE  OPERATOR @ (
        PROCEDURE = vector3d_angle,
        LEFTARG = vector3d,
        RIGHTARG = vector3d
        );

COMMENT ON OPERATOR @(vector3d, vector3d) IS
    'Angle between two vectors in radians.';


CREATE  FUNCTION vector3d_abs_angle(vector3d, vector3d)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_abs_angle(vector3d, vector3d) IS
    'Absolute angle (0 < angle < PI/2) between two vectors in radians.';


CREATE  OPERATOR @+ (
        PROCEDURE = vector3d_abs_angle,
        LEFTARG = vector3d,
        RIGHTARG = vector3d
        );

COMMENT ON OPERATOR @+(vector3d, vector3d) IS
    'Absolute angle (0 < angle < PI/2) between two vectors in radians.';


CREATE  AGGREGATE sum(vector3d) (
        SFUNC=vector3d_add,
        STYPE=vector3d);

COMMENT ON AGGREGATE sum(vector3d) IS
    'Sums vectors.';
   

CREATE  FUNCTION three_point_normal(DOUBLE PRECISION[]) RETURNS vector3d AS
        $$
        DECLARE
            vectors ALIAS FOR $1;
            A vector3d;
            B vector3d;
            C vector3d;
            AB vector3d;
            AC vector3d;
            normal vector3d;
        BEGIN
            A := vectors[1:3];
            B := vectors[4:6];
            C := vectors[7:9];

            AB := A - B;
            AC := A - C;

            -- NORMALIZED CROSS PRODUCT
            normal := vector3d_normalized(AB # AC);

            RETURN normal;
        END;
        $$
        LANGUAGE plpgsql;

COMMENT ON FUNCTION three_point_normal(DOUBLE PRECISION[]) IS
    'Calculates the normal vector of a PLANAR ring using the first three atoms.';



--------------------------------------------------------------------------------
----------------------- ARRAYXI: ARRAY OF INTEGERS -----------------------------
--------------------------------------------------------------------------------



CREATE  DOMAIN arrayxi AS _int4
        CONSTRAINT onedimensional CHECK(ARRAY_NDIMS(VALUE) = 1)
        CONSTRAINT nonulls CHECK(array_has_nulls(VALUE) = FALSE);

COMMENT ON TYPE arrayxi IS 'One-dimensional array of signed integers.';


-------------------------ARRAY CREATION FUNCTIONS-------------------------------


CREATE  FUNCTION arrayxi_constant(size INTEGER, value BIGINT)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_constant(size INTEGER, value BIGINT) IS
    'Returns an array of the given size with all elements set to the given constant value.';


CREATE  FUNCTION arrayxi_lin_spaced(size INTEGER, low INTEGER, high INTEGER)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_lin_spaced(size INTEGER, low INTEGER, high INTEGER) IS
    'Returns an array of the given size with elements equally spaced between low and high.';


CREATE  FUNCTION arrayxi_random(size INTEGER)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C VOLATILE STRICT;

COMMENT ON FUNCTION arrayxi_random(size INTEGER) IS
    'Returns an array of the given size with all elements set to a random value.';


-- ARRAY PROPERTIES


CREATE  FUNCTION arrayxi_size(arrayxi)
        RETURNS INTEGER
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_size(arrayxi) IS 'Returns the number of elements in the array.';


CREATE  OPERATOR #(
        PROCEDURE = arrayxi_size,
        RIGHTARG = arrayxi);

COMMENT ON OPERATOR #(None, arrayxi) IS 'Returns the number of elements in the array.';


CREATE  FUNCTION arrayxi_nonzeros(arrayxi)
        RETURNS INTEGER
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_nonzeros(arrayxi) IS 'Returns the number of non-zero elements in the array.';


CREATE  FUNCTION arrayxi_sum(arrayxi)
        RETURNS BIGINT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_sum(arrayxi) IS 'Sums all the elements of the array.';

CREATE  OPERATOR += (
        PROCEDURE = arrayxi_sum,
        RIGHTARG = arrayxi);

COMMENT ON OPERATOR +=(None, arrayxi) IS 'Returns the sum of all the elements in the array.';


CREATE  FUNCTION arrayxi_mean(arrayxi)
        RETURNS BIGINT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_mean(arrayxi) IS 'Returns the mean value of the array.';


CREATE  FUNCTION abs(arrayxi)
        RETURNS arrayxi
        AS '$libdir/eigen','arrayxi_abs'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION abs(arrayxi) IS 'Returns the absolute of the array.';


CREATE  FUNCTION arrayxi_binary(arrayxi)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_binary(arrayxi) IS
    'Returns a binary version of the array, i.e. all elements > 0 are set to 1.';


------------------------------ARRAY ARITHMETIC----------------------------------


CREATE  FUNCTION arrayxi_add(arrayxi, arrayxi)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_add(arrayxi, arrayxi)
    IS 'Adds two arrays elementwise.';


CREATE  OPERATOR + (
        PROCEDURE = arrayxi_add,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = +);

COMMENT ON OPERATOR +(arrayxi, arrayxi)
    IS 'Adds the first array to the first.';


CREATE  FUNCTION arrayxi_add(arrayxi, scalar INTEGER)
        RETURNS arrayxi
        AS '$libdir/eigen', 'arrayxi_add_scalar'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_add(arrayxi, scalar INTEGER) IS
    'Adds scalar to every element of array.';


CREATE  OPERATOR + (
        PROCEDURE = arrayxi_add,
        LEFTARG = arrayxi,
        RIGHTARG = INTEGER,
        COMMUTATOR = +);

COMMENT ON OPERATOR +(arrayxi, INTEGER) IS
    'Adds scalar to every element of array.';


CREATE  FUNCTION arrayxi_sub(arrayxi, arrayxi)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_sub(arrayxi, arrayxi) IS
    'Subtracts the second array from the first.';


CREATE  OPERATOR - (
        PROCEDURE = arrayxi_sub,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi);

COMMENT ON OPERATOR -(arrayxi, arrayxi) IS
    'Adds two arrays elementwise.';


CREATE  FUNCTION arrayxi_sub(arrayxi, scalar INTEGER)
        RETURNS arrayxi
        AS '$libdir/eigen', 'arrayxi_sub_scalar'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_sub(arrayxi, scalar INTEGER) IS
    'Subtracts scalar from every element of array.';

CREATE  OPERATOR - (
        PROCEDURE = arrayxi_sub,
        LEFTARG = arrayxi,
        RIGHTARG = INTEGER);

COMMENT ON OPERATOR -(arrayxi, INTEGER) IS
    'Subtracts scalar from every element of array.';


CREATE  FUNCTION arrayxi_mul(arrayxi, arrayxi)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_mul(arrayxi, arrayxi) IS
    'Multiplies both arrays elementwise.';


CREATE  OPERATOR * (
        PROCEDURE = arrayxi_mul,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = *);

COMMENT ON OPERATOR *(arrayxi, arrayxi) IS
    'Multiplies both arrays elementwise.';


CREATE  FUNCTION arrayxi_mul(arrayxi, scalar INTEGER)
        RETURNS arrayxi
        AS '$libdir/eigen', 'arrayxi_mul_scalar'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_mul(arrayxi, scalar INTEGER) IS
    'Multiplies scalar with every element of array.';


CREATE  OPERATOR * (
        PROCEDURE = arrayxi_add,
        LEFTARG = arrayxi,
        RIGHTARG = INTEGER,
        COMMUTATOR = *);

COMMENT ON OPERATOR *(arrayxi, INTEGER) IS
    'Multiplies scalar with every element of array.';


----------------------------ARRAY SET ALGEBRA-----------------------------------


CREATE  FUNCTION arrayxi_eq(arrayxi, arrayxi)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_eq(arrayxi, arrayxi) IS
    'Returns true if the elements in both arrays are equal.';


CREATE  OPERATOR = (
        PROCEDURE = arrayxi_eq,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = !=);

COMMENT ON OPERATOR =(arrayxi, arrayxi) IS
    'Returns true if the elements in both arrays are equal.';


CREATE  FUNCTION arrayxi_ne(arrayxi, arrayxi)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_ne(arrayxi, arrayxi) IS
    'Returns true if the arrays are distinct.';


CREATE  OPERATOR != (
        PROCEDURE = arrayxi_ne,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = =);

COMMENT ON OPERATOR !=(arrayxi, arrayxi) IS
    'Returns true if the arrays are distinct.';


CREATE  FUNCTION arrayxi_contains(arrayxi, arrayxi)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_contains(arrayxi, arrayxi) IS
    'Returns true if the first array contains all elements of the second.';


CREATE  OPERATOR @> (
        PROCEDURE = arrayxi_contains,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = <@);

COMMENT ON OPERATOR @>(arrayxi, arrayxi) IS
    'Returns true if the first array contains all elements of the second.';


CREATE  FUNCTION arrayxi_contained(arrayxi, arrayxi)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_contained(arrayxi, arrayxi) IS
    'Returns true if the second array contains all elements of the first.';


CREATE  OPERATOR <@ (
        PROCEDURE = arrayxi_contained,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = @>);

COMMENT ON OPERATOR <@(arrayxi, arrayxi) IS
    'Returns true if the second array contains all elements of the first.';


CREATE  FUNCTION arrayxi_overlaps(arrayxi, arrayxi)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_overlaps(arrayxi, arrayxi) IS
    'Returns true if the arrays have overlapping non-zero elements.';


CREATE  OPERATOR &? (
        PROCEDURE = arrayxi_overlaps,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = &?);

COMMENT ON OPERATOR &?(arrayxi, arrayxi) IS
    'Returns true if the arrays have overlapping non-zero elements.';


CREATE  FUNCTION arrayxi_intersection(arrayxi, arrayxi)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_intersection(arrayxi, arrayxi) IS
    'Returns the intersection of both arrays.';


CREATE  OPERATOR & (
        PROCEDURE = arrayxi_intersection,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = &);

COMMENT ON OPERATOR &(arrayxi, arrayxi) IS
    'Returns the intersection of both arrays.';


CREATE  FUNCTION arrayxi_union(arrayxi, arrayxi)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_union(arrayxi, arrayxi) IS
    'Returns the union of both arrays.';


CREATE  OPERATOR | (
        PROCEDURE = arrayxi_union,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = |);

COMMENT ON OPERATOR |(arrayxi, arrayxi) IS
    'Returns the union of both arrays.';


CREATE  FUNCTION arrayxi_binary_union(arrayxi, arrayxi)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_binary_union(arrayxi, arrayxi) IS
    'Returns the binary union of both arrays.';


-----------------------NORMALIZED SIMILARITY METRICS----------------------------


CREATE  FUNCTION arrayxi_bray_curtis(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_bray_curtis(arrayxi, arrayxi) IS
    'Returns the Bray-Curtis dissimilarity between the arrays.';


CREATE  FUNCTION arrayxi_dice(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_dice(arrayxi, arrayxi) IS
    'Returns the Dice similarity between the arrays.';


CREATE  FUNCTION arrayxi_euclidean(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_euclidean(arrayxi, arrayxi) IS
    'Returns the Euclidean similarity between the arrays.';


CREATE  OPERATOR -> (
        PROCEDURE = arrayxi_euclidean,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = ->);

COMMENT ON OPERATOR ->(arrayxi, arrayxi) IS
    'Returns the Euclidean similarity between the arrays.';


CREATE  FUNCTION arrayxi_kulcz(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_kulcz(arrayxi, arrayxi) IS
    'Returns the Kulczynski similarity between the arrays.';


CREATE  OPERATOR % (
        PROCEDURE = arrayxi_kulcz,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = %);

COMMENT ON OPERATOR %(arrayxi, arrayxi) IS
    'Returns the Kulczynski similarity between the arrays.';


CREATE  FUNCTION arrayxi_manhattan(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_manhattan(arrayxi, arrayxi) IS
    'Returns the Manhattan similarity between the arrays.';


CREATE  OPERATOR ~> (
        PROCEDURE = arrayxi_manhattan,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = ~>);

COMMENT ON OPERATOR ~>(arrayxi, arrayxi) IS
    'Returns the Manhattan similarity between the arrays.';


CREATE  FUNCTION arrayxi_ochiai(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_ochiai(arrayxi, arrayxi) IS
    'Returns the Ochiai similarity between the arrays.';


CREATE  OPERATOR @ (
        PROCEDURE = arrayxi_ochiai,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = @);

COMMENT ON OPERATOR @(arrayxi, arrayxi) IS
    'Returns the Ochiai similarity between the arrays.';


CREATE  FUNCTION arrayxi_russell_rao(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_russell_rao(arrayxi, arrayxi) IS
    'Returns the Russell-Rao similarity between the arrays.';


CREATE  OPERATOR ^ (
        PROCEDURE = arrayxi_russell_rao,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = ^);

COMMENT ON OPERATOR ^(arrayxi, arrayxi) IS
    'Returns the Russell-Rao similarity between the arrays.';


CREATE  FUNCTION arrayxi_simpson(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_simpson(arrayxi, arrayxi) IS
    'Returns the Simpson similarity (FuzCav default) between the arrays.';


CREATE  OPERATOR ^^ (
        PROCEDURE = arrayxi_simpson,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = ^^);

COMMENT ON OPERATOR ^^(arrayxi, arrayxi) IS
    'Returns the Simpson similarity (FuzCav default) between the arrays.';


CREATE  FUNCTION arrayxi_simpson_global(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_simpson_global(arrayxi, arrayxi) IS
    'Returns the global Simpson similarity between the arrays.';


CREATE  FUNCTION arrayxi_tversky(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_tversky(arrayxi, arrayxi) IS
    'Returns the Tversky similarity between the arrays.';


CREATE  OPERATOR %^ (
        PROCEDURE = arrayxi_tversky,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = %^);

COMMENT ON OPERATOR %^(arrayxi, arrayxi) IS
    'Returns the Tversky similarity between the arrays.';


-----ARRAYXI DISTANCE METRICS: USED MOSTLY FOR THE KNN-GIST ORDER BY OPERATORS-----


CREATE FUNCTION arrayxi_dice_dist(arrayxi, arrayxi)
    RETURNS DOUBLE PRECISION
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_dice_dist(arrayxi, arrayxi) IS
    'Returns the Dice distance between two arrays.';


CREATE  OPERATOR <#> (
        PROCEDURE = arrayxi_dice_dist,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = <#>);

COMMENT ON OPERATOR <#>(arrayxi, arrayxi) IS
    'Returns the Dice distance between two arrays.';


CREATE  FUNCTION arrayxi_euclidean_dist(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_euclidean_dist(arrayxi, arrayxi) IS
    'Returns the normalised Euclidean distance between the arrays.';


CREATE  OPERATOR <-> (
        PROCEDURE = arrayxi_euclidean_dist,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = <->);

COMMENT ON OPERATOR <->(arrayxi, arrayxi) IS
    'Returns the normalised Euclidean distance between the arrays.';


CREATE  FUNCTION arrayxi_manhattan_dist(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_manhattan_dist(arrayxi, arrayxi) IS
    'Returns the normalised Manhattan distance between the arrays.';


CREATE  OPERATOR <~> (
        PROCEDURE = arrayxi_manhattan_dist,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = <~>);

COMMENT ON OPERATOR <~>(arrayxi, arrayxi) IS
    'Returns the normalised Manhattan distance between the arrays.';


CREATE FUNCTION arrayxi_kulcz_dist(arrayxi, arrayxi)
    RETURNS DOUBLE PRECISION
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_kulcz_dist(arrayxi, arrayxi) IS
    'Returns the Kulczynski distance between two arrays.';


CREATE  OPERATOR <%> (
        PROCEDURE = arrayxi_kulcz_dist,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi);

COMMENT ON OPERATOR <%>(arrayxi, arrayxi) IS
    'Returns the Kulczynski distance between two arrays.';


CREATE FUNCTION arrayxi_ochiai_dist(arrayxi, arrayxi)
    RETURNS DOUBLE PRECISION
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_ochiai_dist(arrayxi, arrayxi) IS
    'Returns the Ochiai distance between two arrays.';


CREATE  OPERATOR <@> (
        PROCEDURE = arrayxi_ochiai_dist,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = <@>);

COMMENT ON OPERATOR <@>(arrayxi, arrayxi) IS
    'Returns the Ochiai distance between two arrays.';


CREATE FUNCTION arrayxi_russell_rao_dist(arrayxi, arrayxi)
    RETURNS DOUBLE PRECISION
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_russell_rao_dist(arrayxi, arrayxi) IS
    'Returns the Russell-Rao distance between two arrays.';


CREATE  OPERATOR <^> (
        PROCEDURE = arrayxi_russell_rao_dist,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = <^>);

COMMENT ON OPERATOR <^>(arrayxi, arrayxi) IS
    'Returns the Russell-Rao distance between two arrays.';


CREATE FUNCTION arrayxi_simpson_dist(arrayxi, arrayxi)
    RETURNS DOUBLE PRECISION
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_simpson_dist(arrayxi, arrayxi) IS
    'Returns the Simpson distance between two arrays.';


CREATE  OPERATOR <^^> (
        PROCEDURE = arrayxi_simpson_dist,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = <^^>);

COMMENT ON OPERATOR <^^>(arrayxi, arrayxi) IS
    'Returns the Simpson distance between two arrays.';


CREATE FUNCTION arrayxi_tversky_dist(arrayxi, arrayxi)
    RETURNS DOUBLE PRECISION
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_tversky_dist(arrayxi, arrayxi) IS
    'Returns the Tversky distance between two arrays. Parameters alpha and beta have to be set with the set_arrayxi_similarity_limit() function.';


CREATE  OPERATOR <%^> (
        PROCEDURE = arrayxi_tversky_dist,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi);

COMMENT ON OPERATOR <%^>(arrayxi, arrayxi) IS
    'Returns the Tversky distance between two arrays. Parameters alpha and beta have to be set with the set_arrayxi_similarity_limit() function.';


CREATE  FUNCTION arrayxi_mean_hamming_dist(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_mean_hamming_dist(arrayxi, arrayxi) IS
    'Returns the mean Hamming distance between the arrays.';


CREATE  FUNCTION arrayxi_fuzcavsim_global(arrayxi, arrayxi)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_fuzcavsim_global(arrayxi, arrayxi) IS
    'Returns the FuzCav global similarity between the arrays.';


----ARRAYXI BOOLEAN METRICS: COMPARES THE SIMILARITY WITH THE USER-SET LIMIT----
-----------------REQUIRED FOR POSTGRESQL GIST INDEX ON ARRAYXI------------------


CREATE FUNCTION arrayxi_dice_is_above_limit(arrayxi, arrayxi)
    RETURNS BOOLEAN
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_dice_is_above_limit(arrayxi, arrayxi) IS
    'Returns true if the Dice similarity between two arrays is above the user-set limit.';


CREATE  OPERATOR #? (
        PROCEDURE = arrayxi_dice_is_above_limit,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        RESTRICT = contsel,
        JOIN = contjoinsel);

COMMENT ON OPERATOR #?(arrayxi, arrayxi) IS
    'Returns true if the Dice similarity between two arrays is above the user-set limit.';


CREATE FUNCTION arrayxi_euclidean_is_above_limit(arrayxi, arrayxi)
    RETURNS BOOLEAN
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_euclidean_is_above_limit(arrayxi, arrayxi) IS
    'Returns true if the Euclidean similarity between two arrays is above the user-set limit.';


CREATE  OPERATOR ->? (
        PROCEDURE = arrayxi_euclidean_is_above_limit,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        RESTRICT = contsel,
        JOIN = contjoinsel);

COMMENT ON OPERATOR ->?(arrayxi, arrayxi) IS
    'Returns true if the Euclidean similarity between two arrays is above the user-set limit.';


CREATE FUNCTION arrayxi_kulcz_is_above_limit(arrayxi, arrayxi)
    RETURNS BOOLEAN
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_kulcz_is_above_limit(arrayxi, arrayxi) IS
    'Returns true if the Kulczynski similarity between two arrays is above the user-set limit.';


CREATE  OPERATOR %? (
        PROCEDURE = arrayxi_kulcz_is_above_limit,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        RESTRICT = contsel,
        JOIN = contjoinsel);

COMMENT ON OPERATOR %?(arrayxi, arrayxi) IS
    'Returns true if the Kulczynski similarity between two arrays is above the user-set limit.';


CREATE FUNCTION arrayxi_manhattan_is_above_limit(arrayxi, arrayxi)
    RETURNS BOOLEAN
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_manhattan_is_above_limit(arrayxi, arrayxi) IS
    'Returns true if the Manhattan similarity between two arrays is above the user-set limit.';


CREATE  OPERATOR ~>? (
        PROCEDURE = arrayxi_manhattan_is_above_limit,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        RESTRICT = contsel,
        JOIN = contjoinsel);

COMMENT ON OPERATOR ~>?(arrayxi, arrayxi) IS
    'Returns true if the Manhattan similarity between two arrays is above the user-set limit.';


CREATE FUNCTION arrayxi_ochiai_is_above_limit(arrayxi, arrayxi)
    RETURNS BOOLEAN
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_ochiai_is_above_limit(arrayxi, arrayxi) IS
    'Returns true if the Ochiai similarity between two arrays is above the user-set limit.';


CREATE  OPERATOR @? (
        PROCEDURE = arrayxi_ochiai_is_above_limit,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        RESTRICT = contsel,
        JOIN = contjoinsel);

COMMENT ON OPERATOR @?(arrayxi, arrayxi) IS
    'Returns true if the Ochiai similarity between two arrays is above the user-set limit.';


CREATE FUNCTION arrayxi_russell_rao_is_above_limit(arrayxi, arrayxi)
    RETURNS BOOLEAN
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_russell_rao_is_above_limit(arrayxi, arrayxi) IS
    'Returns true if the Russell-Rao similarity between two arrays is above the user-set limit.';


CREATE  OPERATOR ^? (
        PROCEDURE = arrayxi_russell_rao_is_above_limit,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        RESTRICT = contsel,
        JOIN = contjoinsel);

COMMENT ON OPERATOR ^?(arrayxi, arrayxi) IS
    'Returns true if the Russell-Rao similarity between two arrays is above the user-set limit.';


CREATE FUNCTION arrayxi_simpson_is_above_limit(arrayxi, arrayxi)
    RETURNS BOOLEAN
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_simpson_is_above_limit(arrayxi, arrayxi) IS
    'Returns true if the Simpson similarity between two arrays is above the user-set limit.';


CREATE  OPERATOR ^^? (
        PROCEDURE = arrayxi_simpson_is_above_limit,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        RESTRICT = contsel,
        JOIN = contjoinsel);

COMMENT ON OPERATOR ^^?(arrayxi, arrayxi) IS
    'Returns true if the Simpson similarity between two arrays is above the user-set limit.';


CREATE FUNCTION arrayxi_tversky_is_above_limit(arrayxi, arrayxi)
    RETURNS BOOLEAN
    AS '$libdir/eigen'
    LANGUAGE C STRICT IMMUTABLE;

COMMENT ON FUNCTION arrayxi_tversky_is_above_limit(arrayxi, arrayxi) IS
    'Returns true if the Tversky similarity between two arrays is above the user-set limit.';


CREATE  OPERATOR %^? (
        PROCEDURE = arrayxi_tversky_is_above_limit,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        RESTRICT = contsel,
        JOIN = contjoinsel);

COMMENT ON OPERATOR %^?(arrayxi, arrayxi) IS
    'Returns true if the Tversky similarity between two arrays is above the user-set limit.';


-- -- --------POSTGRESQL ARRAYXI DATA TYPE GIST FUNCTIONS AND OPERATOR CLASS----------
-- --
-- --
-- -- CREATE  FUNCTION gist_arrayxi_consistent(internal, arrayxi, smallint, oid, internal)
-- --         RETURNS bool
-- --         AS '$libdir/eigen'
-- --         LANGUAGE C STRICT;
-- --
-- --
-- -- CREATE  FUNCTION gist_arrayxi_union(internal, internal)
-- --         RETURNS internal
-- --         AS '$libdir/eigen'
-- --         LANGUAGE C STRICT;
-- --
-- --
-- -- CREATE  FUNCTION gist_arrayxi_compress(internal)
-- --         RETURNS internal
-- --         AS '$libdir/eigen'
-- --         LANGUAGE C STRICT;
-- --
-- --
-- -- CREATE  FUNCTION gist_arrayxi_decompress(internal)
-- --         RETURNS internal
-- --         AS '$libdir/eigen'
-- --         LANGUAGE C STRICT;
-- --
-- --
-- -- CREATE  FUNCTION gist_arrayxi_penalty(internal, internal, internal)
-- --         RETURNS internal
-- --         AS '$libdir/eigen'
-- --         LANGUAGE C STRICT;
-- --
-- --
-- -- CREATE  FUNCTION gist_arrayxi_picksplit(internal, internal)
-- --         RETURNS internal
-- --         AS '$libdir/eigen'
-- --         LANGUAGE C STRICT;
-- --
-- --
-- -- CREATE  FUNCTION gist_arrayxi_same(internal, internal, internal)
-- --         RETURNS internal
-- --         AS '$libdir/eigen'
-- --         LANGUAGE C STRICT;
-- --
-- --
-- -- CREATE  FUNCTION gist_arrayxi_distance(internal, arrayxi, smallint, oid)
-- --         RETURNS float8
-- --         AS '$libdir/eigen'
-- --         LANGUAGE C STRICT;
-- --
-- --
-- -- CREATE  OPERATOR CLASS arrayxi_gist_ops
-- -- DEFAULT FOR TYPE arrayxi USING gist AS
-- --         OPERATOR  1  #?   (arrayxi,arrayxi), -- DICE SIMILARITY ABOVE LIMIT?
-- --         OPERATOR  2  ->?  (arrayxi,arrayxi), -- EUCLIDEAN ...
-- --         OPERATOR  3  %?   (arrayxi,arrayxi), -- KULCZ ...
-- --         OPERATOR  4  ~>?  (arrayxi,arrayxi), -- MANHATTAN ...
-- --         OPERATOR  5  @?   (arrayxi,arrayxi), -- OCHIAI ..
-- --         OPERATOR  6  ^?   (arrayxi,arrayxi), -- RUSSELL RAO ...
-- --         OPERATOR  7  ^^?  (arrayxi,arrayxi), -- SIMPSON ...
-- --         OPERATOR  8  %^?  (arrayxi,arrayxi), -- TVERSKY ...
-- --         OPERATOR  9  <#>  FOR ORDER BY pg_catalog.float_ops, -- DICE KNN-GIST
-- --         OPERATOR 10  <->  FOR ORDER BY pg_catalog.float_ops, -- EUCLIDEAN KNN-GIST
-- --         OPERATOR 11  <%>  FOR ORDER BY pg_catalog.float_ops, -- KULCZ KNN-GIST
-- --         OPERATOR 12  <~>  FOR ORDER BY pg_catalog.float_ops, -- MANHATTAN KNN-GIST
-- --         OPERATOR 13  <@>  FOR ORDER BY pg_catalog.float_ops, -- OCHIAI KNN-GIST
-- --         OPERATOR 14  <^>  FOR ORDER BY pg_catalog.float_ops, -- RUSSELL-RAO KNN-GIST
-- --         OPERATOR 15  <^^> FOR ORDER BY pg_catalog.float_ops, -- SIMPSON KNN-GIST
-- --         OPERATOR 16  <%^> FOR ORDER BY pg_catalog.float_ops, -- TVERSKY KNN-GIST
-- --         FUNCTION  1  gist_arrayxi_consistent(internal, arrayxi, smallint, oid, internal),
-- --         FUNCTION  2  gist_arrayxi_union(internal, internal),
-- --         FUNCTION  3  gist_arrayxi_compress(internal),
-- --         FUNCTION  4  gist_arrayxi_decompress(internal),
-- --         FUNCTION  5  gist_arrayxi_penalty(internal, internal, internal),
-- --         FUNCTION  6  gist_arrayxi_picksplit(internal, internal),
-- --         FUNCTION  7  gist_arrayxi_same(internal, internal, internal),
-- --         FUNCTION  8  (arrayxi, arrayxi) gist_arrayxi_distance(internal, arrayxi, smallint, oid);



--------------------------------------------------------------------------------
------------------------ ARRAYXD: ARRAY OF DOUBLES -----------------------------
--------------------------------------------------------------------------------



CREATE  DOMAIN arrayxd AS _float8
        CONSTRAINT onedimensional CHECK(ARRAY_NDIMS(VALUE) = 1)
        CONSTRAINT nonulls CHECK(array_has_nulls(VALUE) = FALSE);

COMMENT ON TYPE arrayxd IS
    'One-dimensional array of double precision floats.';

-- ARRAY PROPERTIES

CREATE  FUNCTION arrayxd_size(arrayxd)
        RETURNS INTEGER
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_size(arrayxd) IS
    'Returns the number of elements in the array.';


CREATE  OPERATOR #(
        PROCEDURE = arrayxd_size,
        RIGHTARG = arrayxd);

COMMENT ON OPERATOR #(None, arrayxd) IS
    'Returns the number of elements in the array.';


CREATE  FUNCTION arrayxd_nonzeros(arrayxd)
        RETURNS INTEGER
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_nonzeros(arrayxd) IS
    'Returns the number of non-zero elements in the array.';


CREATE  FUNCTION arrayxd_sum(arrayxd)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_sum(arrayxd) IS
    'Sums all the elements of the array.';

CREATE  OPERATOR += (
        PROCEDURE = arrayxd_sum,
        RIGHTARG = arrayxd);

COMMENT ON OPERATOR +=(None, arrayxd) IS
    'Returns the sum of all the elements in the array.';


CREATE  FUNCTION arrayxd_mean(arrayxd)
        RETURNS BIGINT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_mean(arrayxd) IS
    'Returns the mean value of the array.';


CREATE  FUNCTION abs(arrayxd)
        RETURNS arrayxd
        AS '$libdir/eigen','arrayxd_abs'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION abs(arrayxd) IS
    'Returns the absolute of the array.';


--------------------------- ARRAYXD ARITHMETIC ---------------------------------


CREATE  FUNCTION arrayxd_add(arrayxd, arrayxd)
        RETURNS arrayxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_add(arrayxd, arrayxd) IS
    'Adds two arrays elementwise.';


CREATE  OPERATOR + (
        PROCEDURE = arrayxd_add,
        LEFTARG = arrayxd,
        RIGHTARG = arrayxd,
        COMMUTATOR = +);

COMMENT ON OPERATOR +(arrayxd, arrayxd) IS
    'Subtracts the second array from the first.';


CREATE  FUNCTION arrayxd_add(arrayxd, scalar DOUBLE PRECISION)
        RETURNS arrayxd
        AS '$libdir/eigen', 'arrayxd_add_scalar'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_add(arrayxd, scalar DOUBLE PRECISION) IS
    'Adds scalar to every element of array.';

CREATE  OPERATOR + (
        PROCEDURE = arrayxd_add,
        LEFTARG = arrayxd,
        RIGHTARG = DOUBLE PRECISION,
        COMMUTATOR = +);

COMMENT ON OPERATOR +(arrayxd, DOUBLE PRECISION) IS
    'Adds scalar to every element of array.';


CREATE  FUNCTION arrayxd_sub(arrayxd, arrayxd)
        RETURNS arrayxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_sub(arrayxd, arrayxd) IS
    'Subtracts the second array from the first.';


CREATE  OPERATOR - (
        PROCEDURE = arrayxd_sub,
        LEFTARG = arrayxd,
        RIGHTARG = arrayxd);

COMMENT ON OPERATOR -(arrayxd, arrayxd) IS
    'Adds two arrays elementwise.';


CREATE  FUNCTION arrayxd_sub(arrayxd, scalar DOUBLE PRECISION)
        RETURNS arrayxd
        AS '$libdir/eigen', 'arrayxd_sub_scalar'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_sub(arrayxd, scalar DOUBLE PRECISION) IS
    'Subtracts scalar from every element of array.';

CREATE  OPERATOR - (
        PROCEDURE = arrayxd_sub,
        LEFTARG = arrayxd,
        RIGHTARG = DOUBLE PRECISION);

COMMENT ON OPERATOR -(arrayxd, DOUBLE PRECISION) IS
    'Subtracts scalar from every element of array.';


CREATE  FUNCTION arrayxd_mul(arrayxd, arrayxd)
        RETURNS arrayxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_mul(arrayxd, arrayxd) IS
    'Multiplies both arrays elementwise.';


CREATE  OPERATOR * (
        PROCEDURE = arrayxd_mul,
        LEFTARG = arrayxd,
        RIGHTARG = arrayxd,
        COMMUTATOR = *);

COMMENT ON OPERATOR *(arrayxd, arrayxd) IS
    'Multiplies both arrays elementwise.';


CREATE  FUNCTION arrayxd_mul(arrayxd, scalar DOUBLE PRECISION)
        RETURNS arrayxd
        AS '$libdir/eigen', 'arrayxd_mul_scalar'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_mul(arrayxd, scalar DOUBLE PRECISION) IS
    'Multiplies scalar with every element of array.';

CREATE  OPERATOR * (
        PROCEDURE = arrayxd_add,
        LEFTARG = arrayxd,
        RIGHTARG = DOUBLE PRECISION,
        COMMUTATOR = *);

COMMENT ON OPERATOR *(arrayxd, DOUBLE PRECISION) IS
    'Multiplies scalar with every element of array.';


----------------------- DISTANCE/SIMILARITY METRICS ----------------------------


CREATE  FUNCTION arrayxd_euclidean(arrayxd, arrayxd)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_euclidean(arrayxd, arrayxd) IS
    'Returns the Euclidean distance between the arrays.';


CREATE  FUNCTION arrayxd_manhattan(arrayxd, arrayxd)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_manhattan(arrayxd, arrayxd) IS
    'Returns the Manhattan distance between the arrays.';


CREATE  FUNCTION arrayxd_usrsim(arrayxd, arrayxd)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_usrsim(arrayxd, arrayxd) IS
    'Returns the weighted USR Manhattan distance between the arrays.';


CREATE  FUNCTION arrayxd_usrcatsim(arrayxd, arrayxd, ow REAL DEFAULT 1.0,
                                   hw REAL DEFAULT 0.25, rw REAL DEFAULT 0.25,
                                   aw REAL DEFAULT 0.25, dw REAL DEFAULT 0.25)
        RETURNS DOUBLE PRECISION
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_usrcatsim(arrayxd, arrayxd, REAL, REAL, REAL, REAL, REAL) IS
    'Returns the weighted USR Manhattan distance between the arrays for all 60 moments with optional weights for atom types.';



--------------------------------------------------------------------------------
----------------------- MATRIXXD: MATRIX OF DOUBLES ----------------------------
--------------------------------------------------------------------------------


---------------------------MATRIX CONSTRUCTION METHODS--------------------------


CREATE  FUNCTION matrixxd_identity(rows INTEGER, cols INTEGER)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_identity(rows INTEGER, cols INTEGER) IS
    'Returns an identity matrix of the given dimensions.';


CREATE  FUNCTION matrixxd_constant(rows INTEGER, cols INTEGER, value DOUBLE PRECISION)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_constant(rows INTEGER, cols INTEGER, value DOUBLE PRECISION) IS
    'Returns a matrix of the given dimensions with the given coefficient.';


CREATE  FUNCTION matrixxd_random(rows INTEGER, cols INTEGER)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_random(rows INTEGER, cols INTEGER) IS
    'Returns a matrix of the given dimensions with random coefficients.';


-------------------------------MATRIX PROPERTIES--------------------------------


CREATE  FUNCTION matrixxd_is_identity(matrixxd, prec DOUBLE PRECISION DEFAULT 0.001)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_is_identity(matrixxd, DOUBLE PRECISION) IS
    'Returns true if the given matrix is approximately equal to the identity matrix (not necessarily square), within the given precision.';


CREATE  FUNCTION matrixxd_size(matrixxd)
        RETURNS INTEGER
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_size(matrixxd) IS
    'Returns the number of matrix coefficients.';


CREATE  OPERATOR #(
        PROCEDURE = matrixxd_size,
        RIGHTARG = matrixxd);

COMMENT ON OPERATOR #(None, matrixxd) IS
    'Returns the number of matrix coefficients.';


--------------------------------MATRIX ARITHMETIC-------------------------------


CREATE  FUNCTION matrixxd_add(matrixxd, matrixxd)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_add(matrixxd, matrixxd) IS
    'Add the two matrices together.';


CREATE  OPERATOR +(
        PROCEDURE = matrixxd_add,
        LEFTARG = matrixxd,
        RIGHTARG = matrixxd);

COMMENT ON OPERATOR +(matrixxd, matrixxd) IS
    'Add the two matrices together.';


CREATE  FUNCTION matrixxd_subtract(matrixxd, matrixxd)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_subtract(matrixxd, matrixxd) IS
    'Subtracts the second matrix from the first.';


CREATE  OPERATOR -(
        PROCEDURE = matrixxd_subtract,
        LEFTARG = matrixxd,
        RIGHTARG = matrixxd);

COMMENT ON OPERATOR -(matrixxd, matrixxd) IS
    'Subtracts the second matrix from the first.';


CREATE  FUNCTION matrixxd_multiply(matrixxd, matrixxd)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_multiply(matrixxd, matrixxd) IS
    'Multiplies the matrices.';


CREATE  OPERATOR *(
        PROCEDURE = matrixxd_multiply,
        LEFTARG = matrixxd,
        RIGHTARG = matrixxd);

COMMENT ON OPERATOR *(matrixxd, matrixxd) IS
    'Multiplies the matrices.';


CREATE  FUNCTION matrixxd_scalar_product(matrixxd, DOUBLE PRECISION)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_scalar_product(matrixxd, DOUBLE PRECISION) IS
    'Returns the scalar product.';


CREATE  OPERATOR *(
        PROCEDURE = matrixxd_scalar_product,
        COMMUTATOR = *,
        LEFTARG = matrixxd,
        RIGHTARG = DOUBLE PRECISION);

COMMENT ON OPERATOR *(matrixxd, DOUBLE PRECISION) IS
    'Returns the scalar product.';


CREATE  FUNCTION matrixxd_scalar_division(matrixxd, DOUBLE PRECISION)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_scalar_division(matrixxd, DOUBLE PRECISION) IS
    'Returns the scalar division';


CREATE  OPERATOR /(
        PROCEDURE = matrixxd_scalar_division,
        LEFTARG = matrixxd,
        RIGHTARG = DOUBLE PRECISION);

COMMENT ON OPERATOR /(matrixxd, DOUBLE PRECISION) IS
    'Returns the scalar division';


-------------------------------COL-WISE METHODS---------------------------------


CREATE  FUNCTION matrixxd_cw_mean(matrixxd)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_cw_mean(matrixxd) IS
    'Returns the column-wise mean of the matrix';


CREATE  FUNCTION matrixxd_cw_sum(matrixxd)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_cw_sum(matrixxd) IS
    'Returns the column-wise sum of the matrix';


-------------------------------ROW-WISE METHODS---------------------------------


CREATE  FUNCTION matrixxd_rw_mean(matrixxd)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_rw_mean(matrixxd) IS
    'Returns the row-wise mean of the matrix';


CREATE  FUNCTION matrixxd_rw_sum(matrixxd)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_rw_sum(matrixxd) IS
    'Returns the row-wise sum of the matrix';


-----------------------MATRICES AND OTHER EIGEN OBJECTS-------------------------


-- CREATE  CAST (matrixxd AS vector3d)
--         WITH FUNCTION vector3d(matrixxd)
--         AS ASSIGNMENT;

CREATE  FUNCTION matrixxd_hstack(matrixxd, matrixxd)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_hstack(matrixxd, matrixxd) IS
    'horizontally stacks the second matrix onto the first.';


CREATE  FUNCTION matrixxd_vstack(matrixxd, matrixxd)
        RETURNS matrixxd
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_vstack(matrixxd, matrixxd) IS
    'vertically stacks the second matrix onto the first.';


CREATE  FUNCTION matrixxd_hstack(matrixxd, vector3d)
        RETURNS matrixxd
        AS '$libdir/eigen','matrixxd_hstack_vector3d'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_hstack(matrixxd, vector3d) IS
    'horizontally stacks the vector3d onto the matrixxd';


CREATE  FUNCTION matrixxd_vstack(matrixxd, vector3d)
        RETURNS matrixxd
        AS '$libdir/eigen','matrixxd_vstack_vector3d'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION matrixxd_vstack(matrixxd, vector3d) IS
    'vertically stacks the vector3d onto the matrixxd';

    
CREATE  AGGREGATE avg(vector3d) (
        sfunc = matrixxd_vstack,
        stype = matrixxd,
        finalfunc = matrixxd_cw_mean,
        initcond = '{}');
  
  
CREATE  AGGREGATE concat(vector3d) (
    SFUNC=public.matrixxd_vstack,
    STYPE=matrixxd,
    INITCOND='{}');

COMMENT ON AGGREGATE sum(vector3d) IS
    'Concatenates vectors horizontally.';