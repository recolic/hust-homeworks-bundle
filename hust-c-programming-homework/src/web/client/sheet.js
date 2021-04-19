var sheetInfBuffer = [];

sheetInfBuffer.push({
    head: 'veg-class-set',
    desc: 'Set(add/edit) a vegetable class',
    neededArgList: ['classNum', 'className'],
    optiArgList: []
});

sheetInfBuffer.push({
    head: 'veg-class-ls',
    desc: 'ls vegetable classed',
    neededArgList: [],
    optiArgList: ['code']
});

sheetInfBuffer.push({
    head: 'veg-class-rm',
    desc: 'Remove a vegetable class',
    neededArgList: ['classNum'],
    optiArgList: []
});

sheetInfBuffer.push({
    head: 'veg-info-set',
    desc: 'Set(add/edit) a vegetable info',
    neededArgList: ['vegName', 'classNum', 'neuInfoStr'],
    optiArgList: []
});

sheetInfBuffer.push({
    head: 'veg-info-ls',
    desc: 'ls vegetable infos',
    neededArgList: [],
    optiArgList: ['name-keyword', 'neu-keyword', 'class-code']
});

sheetInfBuffer.push({
    head: 'veg-info-rm',
    desc: 'Remove a vegetable info',
    neededArgList: ['vegName'],
    optiArgList: []
});

sheetInfBuffer.push({
    head: 'job-set',
    desc: 'Set(add/edit) a work',
    neededArgList: ['jobNum', 'vegNum', 'area', 'weight', 'year'],
    optiArgList: []
});

sheetInfBuffer.push({
    head: 'job-ls',
    desc: 'ls works',
    neededArgList: [],
    optiArgList: ['veg-name-keyword', 'veg-name', 'year']
});

sheetInfBuffer.push({
    head: 'job-rm',
    desc: 'Remove a work',
    neededArgList: ['jobNum'],
    optiArgList: []
});

sheetInfBuffer.push({
    head: 'job-report-by-veg-class',
    desc: 'Gen work report by vegetable class',
    neededArgList: [],
    optiArgList: []
});

sheetInfBuffer.push({
    head: 'job-report-by-year-and-veg-name',
    desc: 'Gen work report by year and vegetable name',
    neededArgList: ['yearBegin(include)', 'yearEnd(Not include)'],
    optiArgList: []
});

sheetInfBuffer.push({
    head: 'check-weight-by-veg-class',
    desc: 'List weights by vegetable class',
    neededArgList: ['classNum'],
    optiArgList: []
});

function _makeele(infName, required) {
    var ret = new String('<li><label>');
    ret += infName;
    if(required) {
        ret += ' <span class="required">*</span>';
    }
    ret += '</label><input type="text" id="_ele_id_' + infName;
    ret += '" class="field-long" /></li>';
    return ret;
}

function _makesubmitbtn(sheetinf) {
    var ret = new String('<li><input type="submit" value="Submit" onclick=');
    ret += "'";
    //Make javascript submittion command.
    ret += 'do_cmd("' + sheetinf.head + '"';
    sheetinf.neededArgList.forEach(function(infName){
        ret += ',document.getElementById("_ele_id_'+infName+'").value';
    });
    sheetinf.optiArgList.forEach(function(infName){
        ret += ',"--'+infName+'="+document.getElementById("_ele_id_'+infName+'").value';
    });
    ret += ');';
    //Done.
    ret += "' /></li>";
    return ret;
}

function makeSheetHtml(sheetinf) {
    var ret = new String('<ul class="form-style-1">');
    sheetinf.neededArgList.forEach(function(ele){
        ret += _makeele(ele, true);
    });
    sheetinf.optiArgList.forEach(function(ele){
        ret += _makeele(ele, false);
    });
    ret += _makesubmitbtn(sheetinf);
    ret += '</ul>';
    return ret;
}

function makeSheetHtmlByHead(headStr) {
    var html = null;
    sheetInfBuffer.forEach(function(iinf){
        if(iinf.head.valueOf() == headStr.valueOf()) {
            html = makeSheetHtml(iinf);
        }
    });
    return html;
}

function makeOptions() {
    var ret = new String('');
    ret += '<option value="">Please select your choice</option>';   
    sheetInfBuffer.forEach(function(iinf){
        ret += '<option value="'+iinf.head+'">'+iinf.desc+'</option>';
    });
    return ret;
}