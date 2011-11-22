============
Introduction
============

**pgeigen** is a `PostgreSQL <http://www.postgresql.org/>`_ extension that uses 
the `Eigen <http://eigen.tuxfamily.org>`_ C++ template library to introduce new 
data types and functions suitable for linear algebra.

Installation
------------

Software requirements
~~~~~~~~~~~~~~~~~~~~~
**pgeigen** requires PostgreSQL 9.1+ including development header files (normally 
postgresql-server-dev package or similar) as well as the Eigen header files in
version 3+. The :envvar:`$EIGEN` environment variable has to be set to the path
that contains the Eigen header files, e.g. /usr/local/include/Eigen.

Obtaining the source code
~~~~~~~~~~~~~~~~~~~~~~~~~
The source code for **pgeigen** can be obtained by either downloading a source package
from the `Bitbucket <https://bitbucket.org/aschreyer/pgeigen>`_ repository or
by cloning it with::

    $ hg clone https://bitbucket.org/aschreyer/pgeigen

Installing the extension
~~~~~~~~~~~~~~~~~~~~~~~~
The extension can be built and installed with::

    $ make
    $ sudo make install

This will build and install the shared library in the PostgreSQL server library
directory. The extension can then be installed in the server by executing the following
commands in PostgreSQL (e.g. psql or GUI tool)::

    $ CREATE EXTENSION pgeigen;

Documentation
-------------
This documentation is available from http://pgeigen.readthedocs.org (in progress). 

License
-------
**pgeigen** is released under the `MIT License <http://en.wikipedia.org/wiki/MIT_License>`_.