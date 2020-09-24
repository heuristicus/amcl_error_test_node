This node may be useful to help debug amcl. By default the output from amcl is a warning something like

```
No laser scan received (and thus no pose updates have been published) for 398.853000 seconds.  Verify that data is being published on the /amazon_warehouse_robot/laser/scan topic.
```

Most of the time the laser isn't the actual thing that's causing the problem. The laser is often not received because the message filter used by amcl is not letting any messages through. This node outputs information from the message filter about why messages are being dropped by it, which can help point to the cause of amcl not working.

With the message `The timestamp on the message is more than the cache length earlier than the newest data in the transform cache.`, the problem may be descynhronised clocks between two machines, if you are running a ros master on one machine and some nodes on another.