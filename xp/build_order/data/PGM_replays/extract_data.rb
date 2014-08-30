#!/usr/bin/ruby

class DataBO
  attr_accessor :nb, :last

  def initialize(nb, last)
    @nb = nb
    @last = last
  end
end

def tail(str)
  value = case str
          when "Protoss_Zealot" then 40
          when "Protoss_Dragoon" then 50
          when "Protoss_High_Templar" then 50
          when "Protoss_Dark_Templar" then 50
          when "Protoss_Reaver" then 70
          when "Protoss_Archon" then 20
          when "Protoss_Dark_Archon" then 20
          when "Protoss_Observer" then 40
          when "Protoss_Shuttle" then 60
          when "Protoss_Scout" then 80
          when "Protoss_Carrier" then 140
          when "Protoss_Arbiter" then 160
          when "Protoss_Corsair" then 40
          when "Protoss_Nexus" then 120
          when "Protoss_Assimilator" then 40
          when "Protoss_Gateway" then 60
          when "Protoss_Forge" then 40
          when "Protoss_Shield_Battery" then 30
          when "Protoss_Cybernetics_Core" then 60
          when "Protoss_Photon_Cannon" then 50
          when "Protoss_Robotics_Facility" then 80
          when "Protoss_Stargate" then 70
          when "Protoss_Citadel_of_Adun" then 60
          when "Protoss_Robotics_Support_Bay" then 30
          when "Protoss_Fleet_Beacon" then 60
          when "Protoss_Templar_Archives" then 60
          when "Protoss_Observatory" then 30
          when "Protoss_Arbiter_Tribunal" then 60
          else 0
          end
  return (value * 23.81).round
end

def usage
  puts  "Usage: " + $0 + " FILE <LIMIT>"
end

# We must have at least a file name
if ARGV.length == 0
  usage
  exit
end

limit = -1
if ARGV.length == 2
  limit = ARGV[1].to_i
end


file = File.open(ARGV[0])
coeff = 1.463414634
bo = Hash.new()

# For each line in file
file.each do |line|
  words = line.split(',')

  if limit != -1 and words[0].to_i > limit
    break
  end

  if words[0].to_i == 0
    next
  end
  
  if words[2].include? "Created" or words[2].include? "Morph"
    str = words[4].gsub(" ", "_")
    if not (str.include? "Probe" or str.include? "Pylon" or str.include? "Scarab" or str.include? "Interceptor")  
      if not bo.has_key?(str)
        bo[str] = DataBO.new(0,0)
      end
      bo[str].nb += 1
      bo[str].last = (coeff*words[0].to_i + tail(str)).round
    end
  elsif words[2].include? "FinishUpgrade"
    str = words[3].gsub(" ", "_")
    if (str.include? "Protoss")
      str += "_" + words[4].chomp
    else
      str.chomp!
    end
    if not bo.has_key?(str)
      bo[str] = DataBO.new(0,0)
    end
    bo[str].nb = 1
    bo[str].last = (coeff*words[0].to_i).round
  else
    str = words[3].gsub(" ", "_").chomp
    if not bo.has_key?(str)
      bo[str] = DataBO.new(0,0)
    end
    bo[str].nb = 1
    bo[str].last = (coeff*words[0].to_i).round
  end
end

max = 0
bo.each do |k,v|
  puts "#{k} #{v.nb} #{v.last}"
  if max < v.last
    max = v.last
  end
end

puts max

exit
