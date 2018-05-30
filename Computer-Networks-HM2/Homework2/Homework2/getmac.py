eth = Ether(dst = "ff:ff:ff:ff:ff:ff")
arp = ARP(pdst = '10.240.0.0/16')
ans, unans = srp(eth / arp)
for a in ans:
	print "IP:" + a[1].psrc + "   -----   MAC:" + a[1].hwsrc + "\n"

#se afiseaza si perechea ip-mac pentru containerul rt1
print "IP:" + ans[0][0].psrc + "   -----   MAC:" + a[0][0].hwsrc + "\n"
