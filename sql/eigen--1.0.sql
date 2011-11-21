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



-- SHELL TYPE
CREATE  TYPE vector3d;

CREATE  FUNCTION vector3d_in(cstring)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

CREATE  FUNCTION vector3d_out(vector3d)
        RETURNS cstring
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

CREATE  FUNCTION vector3d_recv(internal)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

CREATE  FUNCTION vector3d_send(vector3d)
        RETURNS BYTEA
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

CREATE  TYPE vector3d (
        INTERNALLENGTH = 24,
        INPUT = vector3d_in,
        OUTPUT = vector3d_out,
        receive = vector3d_recv,
        send = vector3d_send,
        ALIGNMENT = double,
        ELEMENT = float8);

COMMENT ON TYPE vector3d IS 
    'Three-dimensional vector that supports a variety of linear algebra operations.';

CREATE  FUNCTION vector3d_cmp(vector3d, vector3d)
        RETURNS INTEGER
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_cmp(vector3d, vector3d) IS 
    'Compares two vectors.';

CREATE  FUNCTION vector3d_lt(vector3d, vector3d)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_lt(vector3d, vector3d) IS 
    'Returns true if the first vector is shorter than the second.';

CREATE  OPERATOR < (
        PROCEDURE = vector3d_lt,
        LEFTARG = vector3d,
        RIGHTARG = vector3d,
        COMMUTATOR = >,
        NEGATOR = >=,
        RESTRICT = scalarltsel,
        JOIN = scalarltjoinsel);

COMMENT ON OPERATOR <(vector3d, vector3d) IS 
    'Returns true if the first vector is shorter than the second.';

CREATE  FUNCTION vector3d_le(vector3d, vector3d)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_le(vector3d, vector3d) IS 
    'Returns true if the first vector is shorter than or equal to the second.';

CREATE  OPERATOR <= (
        PROCEDURE = vector3d_le,
        LEFTARG = vector3d,
        RIGHTARG = vector3d,
        COMMUTATOR = >=,
        NEGATOR = >,
        RESTRICT = scalarltsel,
        JOIN = scalarltjoinsel);

COMMENT ON OPERATOR <=(vector3d, vector3d) IS 
    'Returns true if the first vector is shorter than or equal to the second.';

CREATE  FUNCTION vector3d_eq(vector3d, vector3d)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_eq(vector3d, vector3d) IS 
    'Returns true if the vectors are identical, i.e. their distance is 0.';

CREATE  OPERATOR = (
        PROCEDURE = vector3d_eq,
        LEFTARG = vector3d,
        RIGHTARG = vector3d,
        COMMUTATOR = =,
        NEGATOR = !=,
        RESTRICT = eqsel,
        JOIN = eqjoinsel);

COMMENT ON OPERATOR =(vector3d, vector3d) IS 
    'Returns true if the vectors are identical, i.e. their distance is 0.';

CREATE  FUNCTION vector3d_ge(vector3d, vector3d)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_ge(vector3d, vector3d) IS 
    'Returns true if the first vector is longer than or equal to the second.';

CREATE  OPERATOR >= (
        PROCEDURE = vector3d_ge,
        LEFTARG = vector3d,
        RIGHTARG = vector3d,
        COMMUTATOR = <=,
        NEGATOR = <,
        RESTRICT = scalargtsel,
        JOIN = scalargtjoinsel);

COMMENT ON OPERATOR >=(vector3d, vector3d) IS 
    'Returns true if the first vector is shorter than or equal to the second.';

CREATE  FUNCTION vector3d_gt(vector3d, vector3d)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_gt(vector3d, vector3d) IS 
    'Returns true if the first vector is longer than or equal to the second.';

CREATE  OPERATOR > (
        PROCEDURE = vector3d_gt,
        LEFTARG = vector3d,
        RIGHTARG = vector3d,
        COMMUTATOR = <,
        NEGATOR = <=,
        RESTRICT = scalargtsel,
        JOIN = scalargtjoinsel);

COMMENT ON OPERATOR >(vector3d, vector3d) IS 
    'Returns true if the first vector is longer than the second.';

CREATE  FUNCTION vector3d_ne(vector3d, vector3d)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_ne(vector3d, vector3d) IS 
    'Returns true if the vectors are distinct.';

CREATE  OPERATOR != (
        PROCEDURE = vector3d_ne,
        LEFTARG = vector3d,
        RIGHTARG = vector3d,
        COMMUTATOR = !=,
        NEGATOR = =,
        RESTRICT = neqsel,
        JOIN = neqjoinsel);

COMMENT ON OPERATOR !=(vector3d, vector3d) IS 
    'Returns true if the vectors are distinct.';

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


CREATE  FUNCTION vector3d_sub(vector3d, vector3d)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_sub(vector3d, vector3d) IS 
    'Subtracts one vector from the other.';

CREATE  OPERATOR - (
        PROCEDURE = vector3d_sub,
        LEFTARG = vector3d,
        RIGHTARG = vector3d);

COMMENT ON OPERATOR -(vector3d, vector3d) IS 
    'Subtracts one vector from the other.';


CREATE  FUNCTION vector3d_div(vector3d, FLOAT)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_div(vector3d, FLOAT) IS 
    'Divides a vector by a scalar.';

CREATE  OPERATOR / (
        PROCEDURE = vector3d_div,
        LEFTARG = vector3d,
        RIGHTARG = FLOAT);

COMMENT ON OPERATOR /(vector3d, FLOAT) IS 
    'Divides a vector by a scalar.';


CREATE  FUNCTION vector3d_mul(vector3d, FLOAT)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_mul(vector3d, FLOAT) IS 
    'Multiplication of a vector with scalar.';

CREATE  OPERATOR * (
        PROCEDURE = vector3d_mul,
        LEFTARG = vector3d,
        RIGHTARG = FLOAT);

COMMENT ON OPERATOR *(vector3d, FLOAT) IS 
    'Multiplication of a vector with scalar.';


CREATE  FUNCTION vector3d_dot(vector3d, vector3d)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_dot(vector3d, vector3d) IS 
    'Dot product between two vectors.';

CREATE  OPERATOR * (
        PROCEDURE = vector3d_dot,
        LEFTARG = vector3d,
        RIGHTARG = vector3d,
        COMMUTATOR = *);

COMMENT ON OPERATOR *(vector3d, vector3d) IS 
    'Dot product between two vectors.';


CREATE  FUNCTION vector3d_norm(vector3d)
        RETURNS FLOAT
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


CREATE  FUNCTION vector3d_normalize(vector3d)
        RETURNS vector3d
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_normalize(vector3d) IS 
    'Normalizes vector.';

CREATE  OPERATOR ^ (
        PROCEDURE = vector3d_normalize,
        RIGHTARG = vector3d
        );

COMMENT ON FUNCTION vector3d_normalize(vector3d) IS 
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
        RETURNS FLOAT
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
        RETURNS FLOAT
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
        RETURNS FLOAT
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


CREATE  FUNCTION sum(vector3d[]) RETURNS vector3d AS
        $$
        SELECT  sum($1[i])
        FROM    generate_series(
                                array_lower($1,1),
                                array_upper($1,1)
                               ) g(i);
        $$
        LANGUAGE SQL IMMUTABLE STRICT;

COMMENT ON FUNCTION sum(vector3d[]) IS 
    'Sums all vectors in an array.';


CREATE  FUNCTION vector3d_avg(vector3d[]) RETURNS vector3d AS
        $$
        SELECT SUM($1) / ARRAY_LENGTH($1,1)
        $$
        LANGUAGE SQL IMMUTABLE STRICT;

COMMENT ON FUNCTION vector3d_avg(vector3d[]) IS 
    'Returns the average vector of all vectors in array.';

CREATE  AGGREGATE avg(vector3d) (
        sfunc = array_append,
        stype = vector3d[],
        finalfunc = vector3d_avg,
        initcond = '{}');

COMMENT ON AGGREGATE avg(vector3d) IS 
    'Averages vectors.';


CREATE  FUNCTION three_point_normal(vector3d[]) RETURNS SETOF vector3d AS
        $$
        DECLARE
            vectors ALIAS FOR $1;
            AB vector3d;
            AC vector3d;
            normal vector3d;
        BEGIN
            AB := vectors[1] - vectors[2];
            AC := vectors[1] - vectors[3];

            -- NORMALIZED CROSS PRODUCT
            normal := vector3d_normalize(AB # AC);

            RETURN NEXT normal;
            RETURN;
        END;
        $$
        LANGUAGE plpgsql;

COMMENT ON FUNCTION three_point_normal(vector3d[]) IS 'Calculates the normal vector of a PLANAR ring using the first three atoms.';



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


-- ARRAY ARITHMETIC


CREATE  FUNCTION arrayxi_add(arrayxi, arrayxi)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_add(arrayxi, arrayxi) IS 'Adds two arrays elementwise.';


CREATE  OPERATOR + (
        PROCEDURE = arrayxi_add,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = +);

COMMENT ON OPERATOR +(arrayxi, arrayxi) IS 'Subtracts the second array from the first.';


CREATE  FUNCTION arrayxi_add(arrayxi, scalar INTEGER)
        RETURNS arrayxi
        AS '$libdir/eigen', 'arrayxi_add_scalar'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_add(arrayxi, scalar INTEGER) IS 'Adds scalar to every element of array.';

CREATE  OPERATOR + (
        PROCEDURE = arrayxi_add,
        LEFTARG = arrayxi,
        RIGHTARG = INTEGER,
        COMMUTATOR = +);

COMMENT ON OPERATOR +(arrayxi, INTEGER) IS 'Adds scalar to every element of array.';


CREATE  FUNCTION arrayxi_sub(arrayxi, arrayxi)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_sub(arrayxi, arrayxi) IS 'Subtracts the second array from the first.';


CREATE  OPERATOR - (
        PROCEDURE = arrayxi_sub,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi);

COMMENT ON OPERATOR -(arrayxi, arrayxi) IS 'Adds two arrays elementwise.';


CREATE  FUNCTION arrayxi_sub(arrayxi, scalar INTEGER)
        RETURNS arrayxi
        AS '$libdir/eigen', 'arrayxi_sub_scalar'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_sub(arrayxi, scalar INTEGER) IS 'Subtracts scalar from every element of array.';

CREATE  OPERATOR - (
        PROCEDURE = arrayxi_sub,
        LEFTARG = arrayxi,
        RIGHTARG = INTEGER);

COMMENT ON OPERATOR -(arrayxi, INTEGER) IS 'Subtracts scalar from every element of array.';


CREATE  FUNCTION arrayxi_mul(arrayxi, arrayxi)
        RETURNS arrayxi
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_mul(arrayxi, arrayxi) IS 'Multiplies both arrays elementwise.';


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


CREATE  FUNCTION arrayxi_contains(arrayxi, arrayxi)
        RETURNS BOOLEAN
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_contains(arrayxi, arrayxi) IS 'Returns true if the first array contains all elements of the second.';


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


-----------------------NORMALIZED SIMILARITY METRICS----------------------------


CREATE  FUNCTION arrayxi_bray_curtis(arrayxi, arrayxi)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_bray_curtis(arrayxi, arrayxi) IS 
    'Returns the Bray-Curtis dissimilarity between the arrays.';
    

CREATE  FUNCTION arrayxi_dice(arrayxi, arrayxi)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_dice(arrayxi, arrayxi) IS 
    'Returns the Dice similarity between the arrays.';
    

CREATE  FUNCTION arrayxi_kulcz(arrayxi, arrayxi)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_kulcz(arrayxi, arrayxi) IS 
    'Returns the Kulczynski similarity between the arrays.';


CREATE  FUNCTION arrayxi_ochiai(arrayxi, arrayxi)
        RETURNS FLOAT
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
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_russell_rao(arrayxi, arrayxi) IS 
    'Returns the Russell-Rao similarity (FuzCav default) between the arrays.';
    

CREATE  FUNCTION arrayxi_simpson(arrayxi, arrayxi)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_simpson(arrayxi, arrayxi) IS 
    'Returns the Simpson similarity (FuzCav default) between the arrays.';
    

CREATE  FUNCTION arrayxi_tversky(arrayxi, arrayxi)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_tversky(arrayxi, arrayxi) IS 
    'Returns the Tversky similarity between the arrays.';


------------------------DISTANCE/SIMILARITY METRICS-----------------------------


CREATE  FUNCTION arrayxi_euclidean_dist(arrayxi, arrayxi)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_euclidean_dist(arrayxi, arrayxi) IS 
    'Returns the Euclidean distance between the arrays.';


CREATE  OPERATOR -> (
        PROCEDURE = arrayxi_euclidean_dist,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = ->);

COMMENT ON OPERATOR ->(arrayxi, arrayxi) IS 
    'Returns the Euclidean distance between the arrays.';


CREATE  FUNCTION arrayxi_manhattan_dist(arrayxi, arrayxi)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_manhattan_dist(arrayxi, arrayxi) IS 
    'Returns the Manhattan distance between the arrays.';


CREATE  OPERATOR ~> (
        PROCEDURE = arrayxi_manhattan_dist,
        LEFTARG = arrayxi,
        RIGHTARG = arrayxi,
        COMMUTATOR = ~>);

COMMENT ON OPERATOR ~>(arrayxi, arrayxi) IS 
    'Returns the Manhattan distance between the arrays.';
  

CREATE  FUNCTION arrayxi_fuzcavsim_global(arrayxi, arrayxi)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxi_fuzcavsim_global(arrayxi, arrayxi) IS 
    'Returns the FuzCav global similarity between the arrays.';



--------------------------------------------------------------------------------
------------------------ ARRAYXI: ARRAY OF DOUBLES -----------------------------
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
        RETURNS BIGINT
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


CREATE  FUNCTION arrayxd_add(arrayxd, scalar INTEGER)
        RETURNS arrayxd
        AS '$libdir/eigen', 'arrayxd_add_scalar'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_add(arrayxd, scalar INTEGER) IS 
    'Adds scalar to every element of array.';

CREATE  OPERATOR + (
        PROCEDURE = arrayxd_add,
        LEFTARG = arrayxd,
        RIGHTARG = INTEGER,
        COMMUTATOR = +);

COMMENT ON OPERATOR +(arrayxd, INTEGER) IS 
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


CREATE  FUNCTION arrayxd_sub(arrayxd, scalar INTEGER)
        RETURNS arrayxd
        AS '$libdir/eigen', 'arrayxd_sub_scalar'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_sub(arrayxd, scalar INTEGER) IS 
    'Subtracts scalar from every element of array.';

CREATE  OPERATOR - (
        PROCEDURE = arrayxd_sub,
        LEFTARG = arrayxd,
        RIGHTARG = INTEGER);

COMMENT ON OPERATOR -(arrayxd, INTEGER) IS 
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


CREATE  FUNCTION arrayxd_mul(arrayxd, scalar INTEGER)
        RETURNS arrayxd
        AS '$libdir/eigen', 'arrayxd_mul_scalar'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_mul(arrayxd, scalar INTEGER) IS 
    'Multiplies scalar with every element of array.';

CREATE  OPERATOR * (
        PROCEDURE = arrayxd_add,
        LEFTARG = arrayxd,
        RIGHTARG = INTEGER,
        COMMUTATOR = *);

COMMENT ON OPERATOR *(arrayxd, INTEGER) IS 
    'Multiplies scalar with every element of array.';


----------------------- DISTANCE/SIMILARITY METRICS ----------------------------


CREATE  FUNCTION arrayxd_euclidean(arrayxd, arrayxd)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_euclidean(arrayxd, arrayxd) IS 
    'Returns the Euclidean distance between the arrays.';


CREATE  FUNCTION arrayxd_manhattan(arrayxd, arrayxd)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_manhattan(arrayxd, arrayxd) IS 
    'Returns the Manhattan distance between the arrays.';


CREATE  FUNCTION arrayxd_usrsim(arrayxd, arrayxd)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_usrsim(arrayxd, arrayxd) IS 
    'Returns the weighted USR Manhattan distance between the arrays.';


CREATE  FUNCTION arrayxd_usrcatsim(arrayxd, arrayxd, ow REAL DEFAULT 1.0, 
                                   hw REAL DEFAULT 0.25, rw REAL DEFAULT 0.25, 
                                   aw REAL DEFAULT 0.25, dw REAL DEFAULT 0.25)
        RETURNS FLOAT
        AS '$libdir/eigen'
        LANGUAGE C IMMUTABLE STRICT;

COMMENT ON FUNCTION arrayxd_usrcatsim(arrayxd, arrayxd, REAL, REAL, REAL, REAL, REAL) IS 
    'Returns the weighted USR Manhattan distance between the arrays for all 60 moments with optional weights for atom types.';