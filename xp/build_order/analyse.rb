#!/usr/bin/ruby

def median(array)
  sorted = array.sort
  len = sorted.length
  return (sorted[(len - 1) / 2] + sorted[len / 2]) / 2.0
end

# ls = %x( ls bo* )
# files = ls.split('\n')

# files.each do |filename|

  # Open file
  # file = File.open(filename)
  file = File.open(ARGV[0])
  
  total = 0
  found = false 
  opt = Array.new
  
  # For each line in file
  file.each do |line|
    words = line.split(': ')
    if words[0].include? "Global cost"
      if words[1].to_i == 0
        found = true;
      else
        found = false;
      end
      total += 1
    end
    if words[0].include? "Optimization cost" and found
      opt.push words[1].to_i
    end
  end

  mean = opt.inject{ |sum, el| sum + el }.to_f / opt.size
  # puts filename
  puts "#{opt.size} / #{total}"
  puts "mean: #{mean}, median: #{median(opt)}\n"
  
# end

exit
