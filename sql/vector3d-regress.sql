drop table dev.vectortest;
create table dev.vectortest
(
    coords vector3d not null
);

-- INSERT RANDOM VECTORS INTO TABLE
insert  into dev.vectortest
select  vector3d_in(('(' || random() * 10 || ',' || random() * 10 || ',' || random() * 10 || ')')::cstring)
from    credo.contacts cs;

-- VECTORIZED: 1505ms, 580ms
select vector3d_norm(coords) from dev.vectortest order by 1 limit 10


select vector3d_norm(vector3d_cross(coords, vector3d_in('(1,2,3)'))) from dev.vectortest order by 1 limit 10



drop table dev.eigen;
create table dev.eigen 
(
coords dev.vector3d not null
);

insert into dev.eigen select dev.vector3d_in(vector3d_out(coords)) from credo.atoms;

select dev.vector3d_norm(dev.vector3d_in('(1,2,3)'))

select vector3d_magnitude(coords) from credo.atoms order by 1 limit 10
select dev.vector3d_norm(coords) as norm from dev.eigen order by 1 limit 10


select dev.vector3d_norm(dev.vector3d_mul(coords, 2)) as norm from dev.eigen order by 1 limit 10



drop table if exists dev.eigen;

create table dev.eigen 
(
coords arrayxi not null
);


insert into dev.eigen
select arrayxi_random(128) from credo.atoms;


--67539ms / -O3: 997ms / -O3 -fomit-frame-pointer: 991ms / -O3 -fomit-frame-pointer -ffast-math: 998ms
with query as (select arrayxi_random(128) as fp)

select arrayxi_fuzcavsim(query.fp, coords)
from dev.eigen, query
order by 1 desc
limit 10