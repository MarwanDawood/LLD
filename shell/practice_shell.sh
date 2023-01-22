declare -l lower
declare -u upper
lower="ABC"
upper="abc"
echo lowercase ${lower}
echo uppercase ${upper}

declare -a array
array[0]=10
array[1]=20
shift #shifts the array
echo ${array[1]}

declare -A map
map["user"]="marwan"
map["pass"]="123"
echo user is ${map["user"]}, password is ${map["pass"]}

y=${x:-"embedded linux"} #declare y with the value of x if x is defined, otherwise the value after colon
echo x is not defined, 
echo $x
echo $y


y=${x:="embedded linux"} #declare y with the value of x if x is defined, otherwise the value after colon and init x as well
echo x and y are defined the same 
echo $x
echo $y

${z:?} #used to check if x is defined or not
