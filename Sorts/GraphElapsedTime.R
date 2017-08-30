library(ggplot2)
library(reshape2)
library(gam)
library(gridExtra)

sorts <- read.csv("sort_times.csv", header = TRUE)

# nanoseconds
sorts$Time.Elapsed = sorts$Time.Elapsed * 1e+9

models <- with(sorts, by(sorts, Algorithm, function(sort){
  gam(data=sort, Time.Elapsed ~ s(Input.Size))
}))

x <- seq(2, 10000, 100)

sort_predictions <- lapply(names(models), function(name){
  model <- get(name, models)
  data.frame(Algorithm = name, Input.Size = x, Time.Elapsed = predict(model, data.frame(Input.Size = x)))
})

sort_predictions <- do.call("rbind", sort_predictions)

nlogn <- data.frame(
  Input.Size = x,
  Time.Elapsed = (x * log10(x)),
  Algorithm = "n log n"
)

nsquared <- data.frame(
  Input.Size = x,
  Time.Elapsed = (x * x),
  Algorithm = "n^2"
)

n <- data.frame(
  Input.Size = x,
  Time.Elapsed = x,
  Algorithm = "n"
)

g1 <- ggplot(sort_predictions, aes(x=Input.Size, y=Time.Elapsed))+
  geom_ribbon(data = n, aes(ymin=0, ymax=Time.Elapsed), alpha=0.1)+
  geom_ribbon(data = nlogn, aes(ymin=n$Time.Elapsed, ymax=Time.Elapsed), fill="green", alpha=0.1)+
  geom_ribbon(data = nsquared, aes(ymin=nlogn$Time.Elapsed, ymax=Time.Elapsed), fill="yellow", alpha=0.1)+
  geom_ribbon(data = n, aes(ymin=0, ymax=Inf), alpha=0.1, fill="red")+
  geom_line(aes(color=Algorithm), size=1, linetype="dotted")+
  geom_smooth(data=sorts, level=0, aes(color=Algorithm))+
  geom_text(x=7500, y=1e+7, label="n log(n)", color="blue")+
  geom_text(x=2500, y=2e+7, label="n^2", parse=TRUE, color="blue")+
  coord_cartesian(ylim = c(0, 3e+7))
  
  
g1

#grid.arrange(g1, g2)

#  scale_y_log10()+
#  scale_x_log10()+
  
  

