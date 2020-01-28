# -*- coding: utf-8 -*-
require "gnuplot"

Gnuplot.open do |gp|
  Gnuplot::Plot.new(gp) do |plot|
    plot.terminal "png"
    plot.output   "gnuplot_sample.png"
    plot.xrange   "[-3:3]"
    f = "sin(x)"
    plot.data << Gnuplot::DataSet.new(f)
  end
  gets
end
