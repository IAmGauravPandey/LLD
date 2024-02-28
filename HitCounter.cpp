vector<int> times, hits;

        times.resize(300);
        hits.resize(300);

    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        int idx = timestamp % 300;
        if (times[idx] != timestamp) {
            times[idx] = timestamp;
            hits[idx] = 1;
        } else {
            ++hits[idx];
        }
    }

    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        int res = 0;
        for (int i = 0; i < 300; ++i) {
            if (timestamp - times[i] < 300) {
                res += hits[i];
            }
        }
        return res;
    }

/*
How to handle concurrent requests?

When two requests update the list simultaneously, there can be race conditions. It’s possible that the request that updated the list first may not be included eventually.

The most common solution is to use a lock to protect the list. Whenever someone wants to update the list (by either adding new elements or removing the tail), a lock will be placed on the container. After the operation finishes, the list will be unlocked.

This works pretty well when you don’t have a large volume of requests or performance is not a concern. Placing a lock can be costly at some times and when there are too many concurrent requests, the lock may potentially block the system and becomes the performance bottleneck.

Distribute the counter

When a single machine gets too many traffic and performance becomes an issue, it’s the perfect time to think of distributed solution. Distributed system significantly reduces the burden of a single machine by scaling the system to multiple nodes, but at the same time adding complexity.

Let’s say we distribute visit requests to multiple machines equally. I’d like to emphasize the importance of equal distribution first. If particular machines get much more traffic than the rest machines, the system doesn’t get to its full usage and it’s very important to take this into consideration when designing the system. In our case, we can get a hash of users email and distribute by the hash (it’s not a good idea to use email directly as some letter may appear much more frequent than the others).

To count the number, each machine works independently to count its own users from the past minute. When we request the global number, we just need to add all counters together.
*/
