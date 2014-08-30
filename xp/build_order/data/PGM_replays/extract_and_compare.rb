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
  return value 
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

  if not (line.include? "Probe" or line.include? "Pylon" or line.include? "Scarab" or line.include? "Interceptor")  
    action = ""
    if words[2].include? "Created" or words[2].include? "Morph"
      action = words[4].gsub(" ", "_")
    elsif words[2].include? "FinishUpgrade"
      action = words[3].gsub(" ", "_")
    else
      action = words[3].gsub(" ", "_").chomp
    end
    sec = ( (coeff*words[0].to_i) / 23.81 + tail(action) ).round
    
    puts "#{sec} #{action}" 
  end

end

exit
