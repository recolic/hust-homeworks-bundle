    "use strict";

    var i;
    function out()
    {
        $("#menu_cont").css({left:-$("#menu_cont").width()});
        $("#mask").fadeOut();
    }
    function huigui(x,y,n,q)
    {
        var i,xb=0,yb=0,fz=0,fm=0,k,a;
        for(i=0;i<n;i++)
        {
            xb+=x[i];
            yb+=y[i];
        }
        xb/=n;
        yb/=n;
        for(i=0;i<n;i++)
        {
            fz+=(x[i]-xb)*(y[i]-yb);
            fm+=(x[i]-xb)*(x[i]-xb);
        }
        k=fz/(fm*1.0);
        a=yb-k*xb;
        k=k.toFixed(q);
        a=a.toFixed(q);
        return k+','+a;
    }
    function pf(a)
    {
        return parseFloat(a);
    }
    function getT(a)
    {
        if(!document.getElementById(a).value)
            return document.getElementById(a).innerText;
        return document.getElementById(a).value;
    }
    //bind event
    $(window).on("load",function()
    {
        var i;
        $("#exp1").css({display:"block"});
    });
    $("#banner_left").on("click",function()
    {
        $("#menu_cont").css({left:"0px"});
        $("#mask").fadeIn();
    });
    $("#mask").on("click",function()
    {
        out();
        $("#float_window").fadeOut();
    });
    var menuLi=$("#menu_ul li");
    for(i=0;i<8;i++)
    {
        let _i=i;
        $(menuLi[i]).on("click",function()
        {
            for(i=0;i<8;i++)
                $("#exp"+(i+1)).css("display","none");
            $("#exp"+(_i+1)).css("display","block");
            out();
        });
    }
    $(menuLi[8]).on("click",function()
    {
        setTimeout(function()
        {
            $("#mask").fadeIn();
            setTimeout(function()
            {
                $("#float_window").fadeIn();

            },300);
        },0);
        out();
    });
    //return key for focus next
    var allInput=document.getElementsByTagName("input");
    for(i=0;i<allInput.length;i++)
    {
        let _i=i;
        allInput[i].addEventListener("keypress",function(event)
        {
            if(event.keyCode==13&&_i<allInput.length-1)
                allInput[_i+1].focus();
        });
    }
    //visit
    $.post("http://59.111.103.218/exp2/visit.php","","");
    //experiment run button
    function e1Run1()
    {
        var arr=vueExp1Swiper1.slides;
        var x=new Array();
        var y=new Array();
        for(i=0;i<arr.length;i++)
        {
            var yi=Math.pow(1/2/Math.PI/pf(arr[i].row1),2);
            y[i]=yi;
            var xi=i*5;
            x[i]=xi;
            arr[i].row2=(yi*10000000).toString().slice(0,10);
        }
        var ans=huigui(x,y,arr.length,13).split(",");
        $("#exp1_result1").text("回归方程 "+"(1/2πf)^2="+ans[0]+"mx+"+ans[1]);
        $("#exp1_result2").text("k="+1/pf(ans[0]));
        $("#exp1_result3").text("mk="+pf(ans[1])/pf(ans[0])+"g");
    }
    function e2Run1()
    {
        var arr=vueExp2Swiper1.slides;
        var l=arr.length;
        var fub=0,fb=0,ub=0,f2b=0,u2b=0;
        for(i=0;i<l;i++)
        {
            var f=pf(arr[i].row1)/1000*pf(document.getElementById("exp2_g").value);
            arr[i].row4=((pf(arr[i].row2)+pf(arr[i].row3))/2).toFixed(2);
            var u=pf(arr[i].row4);
            fb+=f;
            fub+=f*u;
            ub+=u;
            f2b+=f*f;
            u2b+=u*u;
        }
        fub/=l;
        fb/=l;
        ub/=l;
        f2b/=l;
        u2b/=l;
        $("#exp2_result1").html('<span class="ba">FU</span>='+String(fub).slice(0,12));
        $("#exp2_result2").html('<span class="ba">F</span>='+String(fb).slice(0,12));
        $("#exp2_result3").html('<span class="ba">U</span>='+String(ub).slice(0,12));
        $("#exp2_result4").html('<span class="ba">F^2</span>='+String(f2b).slice(0,12));
        $("#exp2_result5").text("k="+String((fub*8-8*ub*fb)/(8*f2b-8*fb*fb)/1000).slice(0,12)+"V/m");
        $("#exp2_result6").text("r="+String((fub-fb*ub)/(Math.sqrt((f2b-fb*fb)*(u2b-ub*ub)))).slice(0,12));
    }
    function e2Run2()
    {
        var arr=vueExp2Swiper2.slides;
        var ub=0;
        for(i=0;i<arr.length;i++)
        {
            var u=Math.abs(pf(arr[i].row1)-pf(arr[i].row2));
            arr[i].row3=u;
            ub+=u;
        }
        ub/=arr.length;
        var sigma=ub/Math.PI/100/(pf(getT("exp2_d1"))+pf(getT("exp2_d2")))/pf(getT("exp2_k"));
        sigma*=10000;
        $("#exp2_result_du").html('<span class="ba">U1-U2</span>='+ub+"mV");
        $("#exp2_result_6").text("σ="+String(sigma).slice(0,9)+"mV/m");
        $("#exp2_result_ur").html('U<span class="half">r</span>='+String(100*Math.abs(sigma-pf(getT("exp2_6")))/pf(getT("exp2_6"))).slice(0,11)+"%");
    }
    function e2Run3()
    {
        var arr1=vueExp2Swiper3.slides,arr2=vueExp2Swiper4.slides;
        var hb=0,db=0;
        for(i=0;i<arr1.length;i++)
        {
            var h=Math.abs(pf(arr1[i].row1)-pf(arr1[i].row2))
                ,d=Math.abs(pf(arr2[i].row1)-pf(arr2[i].row2));;
            arr1[i].row3=String(h).slice(0,6);
            arr2[i].row3=String(d).slice(0,6);
            hb+=h;
            db+=d;
        }
        hb/=arr1.length;
        db/=arr1.length;
        console.log(pf(getT("exp2_rou")));
        $("#exp2_result_hba").html('<span class="ba">h</span>='+hb/1000);
        $("#exp2_result_dba").html('<span class="ba">d</span>='+db);
        var sigma=0.25*pf(getT("exp2_rou"))*pf(getT("exp2_gg"))*db*(hb+0.25*db);
        $("#exp2_result_66").html("σ="+sigma/1000+"N/m");
        $("#exp2_result_urur").html("Ur="+Math.abs(sigma-pf(getT("exp2_66")))/sigma);
    }
    function e3Run1()
    {
        var arr=vueExp3Swiper1.slides
        var x=new Array(),yl=new Array(),yr=new Array();
        for(i=0;i<arr.length;i++)
        {
            x[i]=Math.pow(Math.cos((9-i)*10/180*Math.PI),2);
            yl[i]=pf(arr[i].row1);
            yr[i]=pf(arr[i].row2);
        }
        var k=huigui(x,yl,arr.length,8).split(",")[0],a=huigui(x,yl,arr.length,8).split(",")[1];
        $("#exp3_result1").text("I左="+k.slice(0,15)+"(cos^2(θ))+"+a.slice(0,15));
        console.log(k,a);
        k=huigui(x,yr,arr.length,8).split(",")[0],a=huigui(x,yr,arr.length,8).split(",")[1];
        $("#exp3_result2").text("I右="+k.slice(0,15)+"(cos^2(θ))+"+a.slice(0,15));
    }

    var pi=3.1415926;
    var nanumda=5893e-10;
    var stufact=1.14
    function uncertaina(a,b){
      var sum=0;
      var len=a.length;
      for(var i=0;i<len;i++){
        sum+=(a[i]-b)*(a[i]-b);
      }
      return Math.sqrt(sum/((len-1)*len))
    }
    function fabs(a){
      if(a>=0){
        return a;
      }
      return -a;
    }
    function getC(a){
      return document.getElementsByClassName(a);
    }
    function getI(a){
      return document.getElementById(a);
    }
    function getCvalue(a){
      var array=document.getElementsByClassName(a);
      var ave=0;
      for(var i=0;i<array.length;i++){
        ave+=parseFloat(array[i].value);
      }
      return ave/array.length;
    }
    function getIvalue(a){
      var id=document.getElementById(a);
      return parseFloat(id.value);
    }
    /*转动惯量实验变量名：
      圆柱--yzd，yzh,yzmass,iyz1,iyz2
      圆筒--ytd1,ytd2,yth,ytmass,iyt1,iyt2
      滑块1--hk1d1,hk1d2,hk1h,hk1mass,ihk11,ihk12
      滑块2--hk2d1,hk2d2,hk2h,hk2mass,ihk21,ihk22
      细杆--polel,polemass,ipole1,ipole2
      球--balld,ballmass,iball1,iball2
    */
    function expFiveFunction1(){
      var i01=1.78e-5,i02=2.3e-5;
      var yzd,yzh,yzmass,iyz1,iyz2;
      var ytd1,ytd2,yth,ytmass,iyt1,iyt2;
      var hk1d1,hk1d2,hk1h,hk1mass,ihk11,ihk12;
      var hk2d1,hk2d2,hk2h,hk2mass,ihk21,ihk22;
      var polel,polemass,ipole1,ipole2;
      var balld,ballmass,iball1,iball2;
      yzd=getCvalue('yzd'),yzh=getCvalue('yzh'),yzmass=getIvalue('yzmass');
      ytd1=getCvalue('ytd1'),ytd2=getCvalue('ytd2'),yth=getCvalue('yth'),ytmass=getIvalue('ytmass');
      hk1d1=getCvalue('hk1d1'),hk1d2=getCvalue('hk1d2'),hk1h=getCvalue('hk1h'),hk1mass=getIvalue('hk1mass');
      hk2d1=getCvalue('hk1d1'),hk2d2=getCvalue('hk1d2'),hk2h=getCvalue('hk1h'),hk2mass=getIvalue('hk1mass');
      polel=getCvalue('polel'),polemass=getIvalue('polemass');
      balld=getCvalue('balld'),ballmass=getIvalue('ballmass')
      iyz1=(1e-7)*yzmass*yzd*yzd/8;
      iyt1=(1e-7)*ytmass*(ytd1*ytd1+ytd2*ytd2)/8;
      ihk11=(1e-7)*hk1mass*(((hk1d1*hk1d1+hk1d2*hk1d2)/16)+hk1h*hk1h/12);
      ihk21=(1e-7)*hk2mass*(((hk2d1*hk2d1+hk2d2*hk2d2)/16)+hk2h*hk2h/12);
      ipole1=(1e-7)*polemass*polel*polel/12;
      iball1=(1e-7)*ballmass*balld*balld/10;
      document.getElementById('iyz1').innerHTML=String(iyz1).slice(0,9);
      document.getElementById('iyt1').innerHTML=String(iyt1).slice(0,9);
      document.getElementById('ihk11').innerHTML=String(ihk11).slice(0,9);
      document.getElementById('ihk21').innerHTML=String(ihk21).slice(0,9);
      document.getElementById('ipole1').innerHTML=String(ipole1).slice(0,9);
      document.getElementById('iball1').innerHTML=String(iball1).slice(0,9);
      var t0,t1,nzk,nza;
      t0=getCvalue('t0'),t1=getCvalue('t1');
      nzk=4*pi*pi*iyz1/(t1*t1-t0*t0);
      nza=nzk/(4*pi*pi);
      document.getElementById('t0').innerHTML=String(t0).slice(0,9);
      document.getElementById('t1').innerHTML=String(t1).slice(0,9);
      document.getElementById('nzk').innerHTML=String(nzk).slice(0,9);
      var tzwp,tyz,tyt,tball,tpole;
      tzwp=getCvalue("tzwp"),tyz=getCvalue('tyz'),tyt=getCvalue('tyt'),tball=getCvalue('tball'),tpole=getCvalue('tpole');
      document.getElementById('btzwp').innerHTML=String(tzwp/10).slice(0,9);
      document.getElementById('btyz').innerHTML=String(tyz/10).slice(0,9);
      document.getElementById('btyt').innerHTML=String(tyt/10).slice(0,9);
      document.getElementById('btball').innerHTML=String(tball/10).slice(0,9);
      document.getElementById('btpole').innerHTML=String(tpole/10).slice(0,9);
      tzwp/=10,tyz/=10,tyt=tyt/=10,tball/=10,tpole/=10;
      var izwp=nza*tzwp*tzwp;
      iyt2=nza*tyt*tyt-izwp,iyz2=nza*tyz*tyz-izwp,iball2=nza*tball*tball-i01,ipole2=nza*tpole*tpole-i02;
      document.getElementById('iyt2').innerHTML=String(iyt2).slice(0,9);
      document.getElementById('iyz2').innerHTML=String(iyz2).slice(0,9);
      document.getElementById('izwp').innerHTML=String(izwp).slice(0,9);
      document.getElementById('iball2').innerHTML=String(iball2).slice(0,9);
      document.getElementById('ipole2').innerHTML=String(ipole2).slice(0,9);
      var uryz=fabs(iyz2-iyz1)/iyz1;
      var uryt=fabs(iyt2-iyt1)/iyt1;
      var urball=fabs(iball2-iball1)/iball1;
      var urpole=fabs(ipole2-ipole1)/ipole1;
      document.getElementById('uryz').innerHTML=String(uryz*100).slice(0,4)+'%';
      document.getElementById('uryt').innerHTML=String(uryt*100).slice(0,4)+'%';
      document.getElementById('urball').innerHTML=String(urball*100).slice(0,4)+'%';
      document.getElementById('urpole').innerHTML=String(urpole*100).slice(0,4)+'%';

    }
    /*导热实验变量名：
      样品盘B直径-bdiam,平均值-averagebdiam,厚度-bwidth,平均值-averagebwidth,样品盘质量mass,比热容capacity;
      散热盘C直径-cdiam,平均值-averagecdiam,厚度-cwidth,平均值-averagecwidth;
      发热盘A稳态温度atemp,平均值-averageatemp;
      散热盘C稳态温度ctemp,平均值-averagectemp;
      冷却过程散热盘温度的数组ctempcold，冷却速率coldrate;
      比热容capacity,导热系数numda;
    */
      function expSixIndex(){
      var capacity=370.9;
      var mass=parseFloat(document.getElementById('mass').value);
      var bdiam=document.getElementsByClassName('bdiameter'),averagebdiam=0;
      var bwidth=document.getElementsByClassName('bwidth'),averagebwidth=0;
      for(var i=0;i<bdiam.length;i++){
        averagebdiam+=parseFloat(bdiam[i].value);
        averagebwidth+=parseFloat(bwidth[i].value);
      }
      averagebdiam/=bdiam.length;
      averagebwidth/=bwidth.length;
      var cdiam=document.getElementsByClassName('cdiameter'),averagecdiam=0;
      var cwidth=document.getElementsByClassName('cwidth'),averagecwidth=0;
      for(var i=0;i<cdiam.length;i++){
        averagecdiam+=parseFloat(cdiam[i].value);
        averagecwidth+=parseFloat(cwidth[i].value);
      }
      averagecdiam/=cdiam.length;
      averagecwidth/=cwidth.length;
      document.getElementById('averagebdiam').innerHTML=String(averagebdiam).slice(0,8);
      document.getElementById('averagebwidth').innerHTML=String(averagebwidth).slice(0,8);
      document.getElementById('averagecdiam').innerHTML=String(averagecdiam).slice(0,8);
      document.getElementById('averagecwidth').innerHTML=String(averagecwidth).slice(0,8);
      /*计算样品盘B,C的平均直径与平均厚度*/
      var atemp=document.getElementsByClassName('atemperature'),averageatemp=0;
      for(var i=0;i<atemp.length;i++){
        averageatemp+=parseFloat(atemp[i].value);;
      }
      averageatemp/=atemp.length
      var ctemp=document.getElementsByClassName('ctemperature'),averagectemp=0;
      for(var i=0;i<ctemp.length;i++){
        averagectemp+=parseFloat(ctemp[i].value);
      }
      averagectemp/=ctemp.length;
      document.getElementById('averageatemp').innerHTML=averageatemp;
      document.getElementById('averagectemp').innerHTML=averagectemp;
    /*计算发热盘A,C的稳态温度*/
      var ctempcold=document.getElementsByClassName('ctempcold');
      var ctempcoldnum=new Array(ctempcold.length);
      for(var i=0;i<ctempcold.length;i++){
        ctempcoldnum[i]=parseFloat(ctempcold[i].value);
      }
    /*获取散热盘C的冷却过程的温度*/
      ctempcoldnum.push(averagectemp);
      function sortNumber(a,b)
      {
        return a-b;
      }
      ctempcoldnum.sort(sortNumber);
      var cp;
      for(var i=0;i<ctempcoldnum.length;i++){
        if(ctempcoldnum[i]===averagectemp)
        {
            cp=i;
            break;
        }
      }
      /*在数组里插入T2并排序，便于计算*/
      var sum1=0,sum2=0;
      var ctempcoldcal=new Array();
      for(var i=cp-1;i>cp-6;i--){
        ctempcoldcal[i]=ctempcoldnum[i]
        sum1+=ctempcoldnum[i];
      }
      for(var i=cp;i<cp+5;i++){
        ctempcoldcal[i]=ctempcoldnum[i+1];
        sum2+=ctempcoldnum[i+1];
      }
      var coldrate=(sum2-sum1)/(5*5*30);
      var averagectempcold=coldrate*30;
      document.getElementById('gradT').innerHTML=String(coldrate).slice(0,8);
      /*计算散热盘冷却速率,默认输入的是降序数组,选十组数进行计算*/
    /*变量名：
      样品盘B直径-bdiam,平均值-averagebdiam,厚度-bwidth,平均值-averagebwidth;
      散热盘C直径-cdiam,平均值-averagecdiam,厚度-cwidth,平均值-averagecwidth;
      发热盘A稳态温度atemp,平均值-averageatemp;
      散热盘C稳态温度ctemp,平均值-averagectemp;
      冷却过程散热盘温度的数组ctempcold，冷却速率coldrate;
      导热系数numda;
    */
      var number1=mass*capacity*coldrate/(pi*averagebdiam*averagebdiam);
      var number2=2*(averagecdiam+4*averagecwidth)*averagebwidth/((averageatemp-averagectemp)*(averagecdiam+2*averagecwidth));
      var numda=number1*number2*1000;
      document.getElementById('numda').innerHTML="导热系数λ="+String(numda).slice(0,8)+'W/(m·k)';
      /*计算导热系数*/
      var uaT,ubT=0.057735027,uat=0,ubt=0.057735027;/*detaT和detat的不确定度*/
      var detaT=new Array();
      for(var i=0;i<9;i++){
        detaT[i]=ctempcoldcal[cp-4+i]-ctempcoldcal[cp-5+i];
      }
      function uatcal(a){
        var ave=0,len=a.length;
        for(var i=0;i<len;i++){
          ave+=(a[i]-averagectempcold)*(a[i]-averagectempcold);
        }
        return Math.sqrt(ave/(len*(len-1)));
      }
      uaT=uatcal(detaT);
      var UdetaT=Math.sqrt(stufact*stufact*uaT*uaT+ubT*ubT);
      var exp6Ur=numda*Math.sqrt(UdetaT*UdetaT/(averagectempcold*averagectempcold)+0.0577*0.0577/900)
      document.getElementById('UdetaT').innerHTML='ΔT的不确定度U(ΔT)='+String(UdetaT).slice(0,8)+'°C';
      document.getElementById('Udetat').innerHTML='Δt的不确定度U(Δt)='+'0.057735'+'°C';
      document.getElementById('exp6Ur').innerHTML='不确定度='+String(exp6Ur).slice(0,8)+'°C'+'&nbsp&nbsp&nbsp&nbsp(取置信概率p=0.68)'
    }
    /*光电效应实验变量名:
    截止电压类名usj，平均值averageusj*/
    function expSevenFunction(){
      function ave_array(a){
        var ave=0;
        for(var i=0;i<a.length;i++){
          ave+=parseFloat(a[i].value);
        }
        return ave/a.length;
      }
      function arraysum(a){
        var Sum=0;
        for(var i=0;i<a.length;i++){
          Sum+=a[i];
        }
        return Sum;
      }/*数组求和*/
      /*数组求均值*/
      function arraysumXY(a,b){
        var Sum=0;
        for(var i=0;i<a.length;i++){
          Sum+=(a[i]*b[i]);
        }
        return Sum;
      }/*数组相乘求和*/
      function arrayave(a){
        var ave=0;
        for(var i=0;i<a.length;i++){
          ave+=(a[i]);
        }
        return ave/a.length;
      }
      function arrayaveXY(a,b){
        var ave=0,len=a.length;
        for(var i=0;i<len;i++){
          ave+=(a[i]*b[i]);
        }
        return ave/len;
      }/*数组相乘求均值*/
      function leastSquMethod(arrayX,arrayY){
          var a,b;
          var aX=0,aY=0,aXY=0,aXX=0,sX=0,sY=0,sXY=0,sXX=0,len=arrayX.length;
          aX=arrayave(arrayX),aY=arrayave(arrayY),aXY=arrayaveXY(arrayX,arrayY),aXX=arrayaveXY(arrayX,arrayX);
          /*sX=arraysum(arrayX),sY=arraysum(arrayY),sXY=arraysumXY(arrayX,arrayY),sXX=arraysumXY(arrayX,arrayY);*/
          a=(aXY-aX*aY)/(aXX-aX*aX);
          b=aY-a*aX;
          return a+','+b
      }
      var averageus1=0,averageus2=0,averageus3=0,averageus4=0,averageus5=0;
      var us1=getC('us1'),us2=getC('us2'),us3=getC('us3'),us4=getC('us4'),us5=getC('us5');
      averageus1=ave_array(us1),averageus2=ave_array(us2),averageus3=ave_array(us3),averageus4=ave_array(us4),averageus5=ave_array(us5);
      document.getElementById('averageus1').innerHTML=averageus1;
      document.getElementById('averageus2').innerHTML=averageus2;
      document.getElementById('averageus3').innerHTML=averageus3;
      document.getElementById('averageus4').innerHTML=averageus4;
      document.getElementById('averageus5').innerHTML=averageus5;
      var frequncy=new Array();
      frequncy[0]=8.214,frequncy[1]=7.408,frequncy[2]=6.873,frequncy[3]=5.490,frequncy[4]=5.196;
      var us=new Array();
      us[0]=averageus1,us[1]=averageus2,us[2]=averageus3,us[3]=averageus5,us[4]=averageus5;
      for(var i=0;i<us.length;i++){us[i]=fabs(us[i]);}
      var hgv=leastSquMethod(frequncy,us);
      var hg=hgv.split(',');
      var htest=hg[0]*1.6*(1e-33);
      var nu0=fabs(hg[1]/hg[0])*(1e+14);
      var Ur=fabs(6.62916-htest*(1e+34))/6.62916;
      document.getElementById('exp7_result1').innerHTML='普朗克常数h='+fabs(htest);
      document.getElementById('exp7_result2').innerHTML='截止频率V<span class="half">0</span>='+nu0;
      document.getElementById('exp7_result3').innerHTML='相对不确定度Ur='+Ur;

    }
    function expEightFunction(){
      function avearray(a){
        var ave=0,len=a.length;
        for(var i=0;i<len;i++){
          ave+=a[i];
        }
        return ave/len;
      }
      var tweleft1=getIvalue('tweleft1'),tweleft2=getIvalue('tweleft2'),tweleft3=getIvalue('tweleft3'),tweleft4=getIvalue('tweleft4'),tweleft5=getIvalue('tweleft5');
      var tweright1=getIvalue('tweright1'),tweright2=getIvalue('tweright2'),tweright3=getIvalue('tweright3'),tweright4=getIvalue('tweright4'),tweright5=getIvalue('tweright1');
      var twediam1=tweleft1-tweright1,twediam2=tweleft2-tweright2,twediam3=tweleft3-tweright3,twediam4=tweleft4-tweright4,twediam5=tweleft5-tweright5;
      document.getElementById('twediam1').innerHTML=String(twediam1).slice(0,10);
      document.getElementById('twediam2').innerHTML=String(twediam2).slice(0,10);
      document.getElementById('twediam3').innerHTML=String(twediam3).slice(0,10);
      document.getElementById('twediam4').innerHTML=String(twediam4).slice(0,10);
      document.getElementById('twediam5').innerHTML=String(twediam5).slice(0,10);
      var twediam=new Array();
      twediam[0]=twediam1*1e-3;
      twediam[1]=twediam2*1e-3;
      twediam[2]=twediam3*1e-3;
      twediam[3]=twediam4*1e-3;
      twediam[4]=twediam5*1e-3;
      var twediamave=avearray(twediam);
      document.getElementById('twediamave').innerHTML=String(twediamave*1e+3).slice(0,10);
      var tenleft1=getIvalue('tenleft1'),tenleft2=getIvalue('tenleft2'),tenleft3=getIvalue('tenleft3'),tenleft4=getIvalue('tenleft4'),tenleft5=getIvalue('tenleft5');
      var tenright1=getIvalue('tenright1'),tenright2=getIvalue('tenright2'),tenright3=getIvalue('tenright3'),tenright4=getIvalue('tenright4'),tenright5=getIvalue('tenright1');
      var tendiam1=tenleft1-tenright1,tendiam2=tenleft2-tenright2,tendiam3=tenleft3-tenright3,tendiam4=tenleft4-tenright4,tendiam5=tenleft5-tenright5;
      document.getElementById('tendiam1').innerHTML=String(tendiam1).slice(0,10);
      document.getElementById('tendiam2').innerHTML=String(tendiam2).slice(0,10);
      document.getElementById('tendiam3').innerHTML=String(tendiam3).slice(0,10);
      document.getElementById('tendiam4').innerHTML=String(tendiam4).slice(0,10);
      document.getElementById('tendiam5').innerHTML=String(tendiam5).slice(0,10);
      var tendiam=new Array();
      tendiam[0]=tendiam1*1e-3;
      tendiam[1]=tendiam2*1e-3;
      tendiam[2]=tendiam3*1e-3;
      tendiam[3]=tendiam4*1e-3;
      tendiam[4]=tendiam5*1e-3;
      var tendiamave=avearray(tendiam);
      document.getElementById('tendiamave').innerHTML=String(tendiamave*1e+3).slice(0,10);
      var radius=((twediamave*twediamave-tendiamave*tendiamave)/(4*10*nanumda));
      document.getElementById('radius').innerHTML='牛顿环曲率半径R='+String(radius).slice(0,10);
      var ltweua=uncertaina(twediam,twediamave);
      var tweua=stufact*ltweua;
      var tweub=5.77e-7;
      var tweu=Math.sqrt(tweua*tweua+tweub*tweub);
      document.getElementById('tweua').innerHTML=String(tweua).slice(0,10);
      document.getElementById('tweub').innerHTML=String(tweub).slice(0,10);
      document.getElementById('tweu').innerHTML=String(tweu).slice(0,10);
      var ltenua=uncertaina(tendiam,tendiamave);
      var tenua=stufact*ltenua;
      var tenub=5.77e-7;
      var tenu=Math.sqrt(tenua*tenua+tenub*tenub);
      document.getElementById('tenua').innerHTML=String(tenua).slice(0,10);
      document.getElementById('tenub').innerHTML=String(tenub).slice(0,10);
      document.getElementById('tenu').innerHTML=String(tenu).slice(0,10);
      var exp8ur=Math.sqrt(4*(ltweua*ltweua*twediamave*twediamave-ltenua*ltenua*tendiamave*tendiamave)/((twediamave*twediamave-tendiamave*tendiamave)*(twediamave*twediamave-tendiamave*tendiamave))+0.00001);
      document.getElementById('exp8ur').innerHTML="合成不确定度U="+String(exp8ur).slice(0,10);
    }
