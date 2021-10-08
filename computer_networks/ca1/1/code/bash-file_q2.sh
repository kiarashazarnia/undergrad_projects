# sudo bash
ovs-vsctl del-br s1
#ovs-vsctl del-br s2
ip link delete s1-eth1
ip link delete s1-eth2
ip link delete s1-eth3
ip link delete s1-eth4
ip netns delete h1
ip netns delete h2
ip netns delete h3
ip netns delete h4

ip netns add h1
ip netns add h2
ip netns add h3
ip netns add h4

ovs-vsctl add-br s1
#ovs-vsctl add-br s2

ip link add h1-eth0 type veth peer name s1-eth1
ip link add h2-eth0 type veth peer name s1-eth2
ip link add h3-eth0 type veth peer name s1-eth3
ip link add h4-eth0 type veth peer name s1-eth4
# ip link show

ip link set h1-eth0 netns h1
ip link set h2-eth0 netns h2
ip link set h3-eth0 netns h3
ip link set h4-eth0 netns h4
# ip netns exec h1 ip link show
# ip netns exec h2 ip link show
# ip netns exec h3 ip link show

ovs-vsctl add-port s1 s1-eth1
ovs-vsctl add-port s1 s1-eth2
ovs-vsctl add-port s1 s1-eth3
ovs-vsctl add-port s1 s1-eth4
#ovs-vsctl add-port s2 s2-eth2
# ovs-vsctl show

#ovs-vsctl set-controller s1 tcp:127.0.0.1
#ovs-controller ptcp: &
#ovs-vsctl set-controller s2 tcp:127.0.0.1
#ovs-controller ptcp: &
# ovs-vsctl show

ip netns exec h1 ifconfig h1-eth0 10.0.0.1
ip netns exec h1 ifconfig lo up
ip netns exec h2 ifconfig h2-eth0 10.0.0.2
ip netns exec h2 ifconfig lo up
ip netns exec h3 ifconfig h3-eth0 10.0.0.3
ip netns exec h3 ifconfig lo up
ip netns exec h4 ifconfig h4-eth0 10.0.0.4
ip netns exec h4 ifconfig lo up
ifconfig s1-eth1 up
ifconfig s1-eth2 up
ifconfig s1-eth3 up
ifconfig s1-eth4 up
#ifconfig s2-eth2 up

ip netns exec h1 ping 10.0.0.3
