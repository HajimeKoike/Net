# -*- coding: utf-8 -*-
 require "gnuplot"
 
Gnuplot.open do |gp|
	Gnuplot::Plot.new( gp ) do |plot|
		plot.title  'test'
		plot.ylabel 'ylabel'
		plot.xlabel 'xlabel'
 
		# グラフ1個目
		x = (-100..100).collect {|v| v.to_f}
		y = (-100..100).collect {|v| v.to_f ** 2}
		plot.data << Gnuplot::DataSet.new( [x, y] ) do |ds|
			ds.with = "lines"
			ds.notitle
		end
 
		# グラフ2個目
		x = (-100..100).collect {|v| v.to_f+50}
		y = (-100..100).collect {|v| v.to_f ** 2}
		plot.data << Gnuplot::DataSet.new( [x, y] ) do |ds|
			ds.with = "lines"
			ds.notitle
		end
 
		# グラフ3個目
		x = (-100..100).collect {|v| v.to_f+100}
		y = (-100..100).collect {|v| v.to_f ** 2}
		plot.data << Gnuplot::DataSet.new( [x, y] ) do |ds|
			ds.with = "lines"
			ds.notitle
		end
	end
end
