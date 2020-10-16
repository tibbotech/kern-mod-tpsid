# kern-mod-tpsid
The module, provides LTPS ID.

The module is loaded by compatible="tpsid" dts node, but it is out-of-tree, so better
```
cp tpsid.conf ${sysconfdir}/modules-load.d/
```
to load sooner.

Provides
```
/proc/tpsid - ID in binary representation
/proc/tpsidt - ID in text representation
```
On am335x is got from FUSE emac, on sp7021 it git from eth0 OTP mac.
