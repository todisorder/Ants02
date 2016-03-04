#set parametric; plot "1/AntPos.txt" w l, "1.5/AntPos.txt" w l, "2/AntPos.txt" w l, "2.5/AntPos.txt" w l, "3/AntPos.txt" w l,  "3.5/AntPos.txt" w l,  "4/AntPos.txt" w l
#unset parametric; plot "1/AntPos.txt" using 2 w l, "1.5/AntPos.txt" using 2 w l, "2/AntPos.txt" using 2 w l, "2.5/AntPos.txt" using 2 w l, "3/AntPos.txt" using 2 w l,  "3.5/AntPos.txt" using 2 w l,  "4/AntPos.txt" using 2 w l
#unset parametric; plot "1/AntVelRadius.txt" w l, "1.5/AntVelRadius.txt" w l, "2/AntVelRadius.txt" w l, "2.5/AntVelRadius.txt" w l, "3/AntVelRadius.txt" w l,  "3.5/AntVelRadius.txt" w l,  "4/AntVelRadius.txt" w l

set parametric; plot "popo/AntPos.txt" w l #, "popo3/AntPos.txt" w l
