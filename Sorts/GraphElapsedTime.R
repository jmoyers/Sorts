library(reshape2)
library(ggplot2)

read.csv("sort_times.csv", header = TRUE) -> sorts

ggplot(sorts, aes(x=Input.Size,
                  y=Time.Elapsed,
                  color=Algorithm)) +
  geom_point() +
  geom_smooth()
