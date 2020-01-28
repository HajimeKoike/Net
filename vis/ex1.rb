#! /usr/local/bin/ruby
#-----------------------------------------------
# Ruby script to draw a graph by gnuplot.(Ex.1)
#-----------------------------------------------
require 'gnuplot'

Gnuplot.open do |gp|
  Gnuplot::Plot.new(gp) do |plot|
    plot.xrange "[-10:10]"
    plot.title  "作成例１"
    plot.xlabel "x"
    plot.ylabel "y"
    plot.grid

    plot.data << Gnuplot::DataSet.new("sin(x)") do |ds|
      ds.with      = "lines"
      ds.linewidth = 2
    end

    plot.data << Gnuplot::DataSet.new("cos(x)") do |ds|
      ds.with      = "lines"
      ds.linewidth = 2
    end
  end
end
