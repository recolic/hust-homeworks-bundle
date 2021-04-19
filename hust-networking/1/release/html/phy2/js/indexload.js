var i;

var vueExp1Swiper1=new Vue({
    el:"#vue_exp1_swiper1",
    data:{
        slides:[]
    }
})
for(i=0;i<6;i++)
{
    vueExp1Swiper1.slides.push({"message":5*i,"row1":"","row2":""});
}
setTimeout(function()
{
    var exp1_swiper1 = new Swiper('.exp1-swiper1-container',{
        slidesPerView: 3.5,
        freeMode:true,
    });
},0);
/*
var vueExp1Swiper2=new Vue({
    el:"#vue_exp1_swiper2",
    data:{
        slides:[]
    }
})
for(i=0;i<30;i++)
{
    vueExp1Swiper2.slides.push({"message":i+1});
}
setTimeout(function()
{
    var mySwiper2 = new Swiper('.exp1-swiper2-container',{
        slidesPerView: 5.5,
        freeMode:true,
    });
},0);

var vueExp1Swiper3=new Vue({
    el:"#vue_exp1_swiper3",
    data:{
        slides:[]
    }
})
for(i=0;i<20;i++)
{
    vueExp1Swiper3.slides.push({"message":i+1});
}
setTimeout(function()
{
    var mySwiper3 = new Swiper('.exp1-swiper3-container',{
        slidesPerView: 5.5,
        freeMode:true,
    });
},0);
*/
var vueExp2Swiper1=new Vue({
    el:"#vue_exp2_swiper1",
    data:{
        slides:[]
    }
})
for(i=1;i<=8;i++)
{
    vueExp2Swiper1.slides.push({"message":i,"row1":"","row2":"","row3":"","row4":""});
}
setTimeout(function()
{
    var exp2_swiper1 = new Swiper('.exp2-swiper1-container',{
        slidesPerView: 4.5,
        freeMode:true,
    });
},0);
var vueExp2Swiper2=new Vue({
    el:"#vue_exp2_swiper2",
    data:{
        slides:[]
    }
})

for(i=1;i<=5;i++)
{
    vueExp2Swiper2.slides.push({"message":i,"row1":"","row2":"","row3":""});
}
setTimeout(function()
{
    var exp2_swiper2 = new Swiper('.exp2-swiper2-container',{
        slidesPerView: 3.5,
        freeMode:true,
    });
},0);

var vueExp2Swiper3=new Vue({
    el:"#vue_exp2_swiper3",
    data:{
        slides:[]
    }
})
for(i=1;i<=5;i++)
{
    vueExp2Swiper3.slides.push({"message":i,"row1":"","row2":"","row3":""});
}
setTimeout(function()
{
    var exp2_swiper3 = new Swiper('.exp2-swiper3-container',{
        slidesPerView: 3.5,
        freeMode:true,
    });
},0);

var vueExp2Swiper4=new Vue({
    el:"#vue_exp2_swiper4",
    data:{
        slides:[]
    }
})
for(i=1;i<=5;i++)
{
    vueExp2Swiper4.slides.push({"message":i,"row1":"","row2":"","row3":""});
}
setTimeout(function()
{
    var exp2_swiper4 = new Swiper('.exp2-swiper4-container',{
        slidesPerView: 3.5,
        freeMode:true,
    });
    $("#exp2").css("display","none");
},0);

var vueExp3Swiper1=new Vue({
    el:"#vue_exp3_swiper1",
    data:{
        slides:[]
    }
})
for(i=1;i<=10;i++)
{
    vueExp3Swiper1.slides.push({"message":i});
}
setTimeout(function()
{
    var exp3_swiper1 = new Swiper('.exp3-swiper1-container',{
        slidesPerView: 3.5,
        freeMode:true,
    });
    $("#exp3").css("display","none");
},0);
/*var mySwiper2 = new Swiper('.exp3-swiper2-container',{
    slidesPerView: 1.8,
    freeMode:true
});
var mySwiper3 = new Swiper('.exp3-swiper3-container',{
    slidesPerView: 1.8,
    freeMode:true
});
 var mySwiper4 = new Swiper('.exp4-swiper1-container',{
     slidesPerView: 2.2,
     freeMode:true
});
var mySwiper5 = new Swiper('.exp4-swiper2-container',{
    slidesPerView: 2.2,
    freeMode:true
});
var mySwiper6 = new Swiper('.exp4-swiper3-container',{
    slidesPerView: 2.2,
    freeMode:true
});
var mySwiper7 = new Swiper('.exp5-swiper1-container',{
    slidesPerView: 2.2,
    freeMode:true
});
var mySwiper8 = new Swiper('.exp1-swiper1-container',{
    slidesPerView: 2.2,
    freeMode:true
});
var mySwiper9 = new Swiper('.exp8-swiper1-container',{
    slidesPerView: 1.1,
    freeMode:true
});
var mySwiper10 = new Swiper('.exp8-swiper2-container',{
    slidesPerView: 1.2,
    freeMode:true
});
var mySwiper11 = new Swiper('.exp8-swiper3-container',{
    slidesPerView: 2.2,
    freeMode:true
});
var mySwiper12 = new Swiper('.exp8-swiper4-container',{
    slidesPerView: 2.2,
    freeMode:true
});
var mySwiper13 = new Swiper('.exp7-swiper1-container',{
    slidesPerView: 2.2,
    freeMode:true
});
var mySwiper14 = new Swiper('.exp7-swiper2-container',{
    slidesPerView: 2.2,
    freeMode:true
});
var mySwiper15 = new Swiper('.exp7-swiper3-container',{
    slidesPerView: 2.2,
    freeMode:true
});
var mySwiper16 = new Swiper('.exp7-swiper4-container',{
    slidesPerView: 2.2,
    freeMode:true
});
var mySwiper17 = new Swiper('.exp2-swiper1-container',{
    slidesPerView: 1.1,
    freeMode:true
});
var mySwiper18 = new Swiper('.exp5-swiper2-container',{
    slidesPerView: 2.2,
    freeMode:true
});
var mySwiper19 = new Swiper('.exp6-swiper1-container',{
    slidesPerView: 3.1,
    freeMode:true
});
*/
var swiper51=new Swiper(".exp5-swiper1-container",{
  freeMode:true,
  slidesPerView: 4.5
})
var swiper52=new Swiper(".exp5-swiper2-container",{
  freeMode:true,
  slidesPerView: 4.5
})
var swiper53=new Swiper(".exp5-swiper3-container",{
  freeMode:true,
  slidesPerView: 4.5
})
var swiper54=new Swiper(".exp5-swiper4-container",{
  freeMode:true,
  slidesPerView: 3.5
})

var swiper61=new Swiper(".exp6-swiper2-container",{
  freeMode:true,
  slidesPerView: 4.5
});
var swiper62=new Swiper(".exp6-swiper1-container",{
  freeMode:true,
  slidesPerView: 4.5
});
var swiper63=new Swiper(".exp6-swiper3-container",{
  freeMode:true,
  slidesPerView: 4.5
})
var swiper71=new Swiper(".exp7-swiper1-container",{
  freeMode:true,
  slidesPerView: 4.5
});
var swiper81=new Swiper(".exp8-swiper1-container",{
  freeMode:true,
  slidesPerView: 3.5
})

$("#exp4,#exp5,#exp6,#exp7,#exp8").css("display","none");
