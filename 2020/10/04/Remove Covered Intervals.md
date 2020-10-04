# Remove Covered Intervals
[LeetCode](https://leetcode.com/problems/remove-covered-intervals/)

```java
class Solution {
    public int removeCoveredIntervals(int[][] rawIntervals) {
        final List<Interval> intervals = Arrays.stream(rawIntervals).map(i -> new Interval(i[0], i[1])).collect(Collectors.toList());
        return (int) intervals.stream().filter(i -> isNotCoveredByOtherIntervals(i, intervals)).count();
    }
    
    private boolean isNotCoveredByOtherIntervals(final Interval i, final List<Interval> all) {
        return all.stream().filter(any -> i.isCoveredBy(any)).count() == 1;
    }
    
    private class Interval {
        
        private final int from;
        
        private final int to;
        
        public Interval(final int from, final int to) {
            this.from = from;
            this.to = to;
        }
        
        public boolean isCoveredBy(final Interval other) {
            return (from >= other.from) && (to <= other.to);
        }
    }
}
```
