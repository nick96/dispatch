Dispatch - A slurm-like job scheduler
=========================================

+------------------------+------------+
| OS                     |  Status    |
+========================+============+
| Linux (AMD64/ARM64)    | |travis|   |
+------------------------+------------+
| Windows (AMD64)        | |appveyor| |
+------------------------+------------+

.. |travis| image:: https://travis-ci.com/nick96/dispatch.svg?branch=master

.. |appveyor| image:: https://ci.appveyor.com/api/projects/status/dj259ujw6p49x5ot?svg=true


This is a fun project, not intended for actual use, to implement a subset of the
functionality available in Slurm.

`dispatchctl`
-------------

Daemon that runs on the control server. Jobs are submitted to the controller and
it handles scheduling them amongst the minions.

`dispatchd`
-----------

Daemon that runs on the minion servers. The controller dispatches jobs to this
daemon and can query its status. `dispatchd` notifies `dispatchctl` when the job
has finished and what the job status is.
