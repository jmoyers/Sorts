library(reshape)
read.csv("sort_times.csv", header = TRUE) -> sorts
cast(sorts, Algorithm ~ Input.Size) -> sorts
matplot(t(sorts), type = "b", pch = 15:19, col = c(1:5), xlab = "Input Size", ylab = "Time Elapsed (s)")
legend("topleft", inset = 0.01, col = c(1:5), legend = sorts$Algorithm, pch = 15:19, bg = ("white"), horiz = F)