Dispatch - A slurm-like job scheduler
=========================================

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
