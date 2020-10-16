# kern-mod-tpsid
The module, provides LTPS ID.

The module is loaded by compatible="tpsid" dts node, but it is out-of-tree, so better
```
cp tpsid.conf ${sysconfdir}/modules-load.d/
```
to load sooner.
