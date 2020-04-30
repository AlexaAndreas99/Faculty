var i = 0;

function changeImage() {
    i += 1;
    if (i == 1) {
        var s = "../lab4html/img/img1.jpg";
    }
    if (i == 2) {
        var s = "../lab4html/img/img3.png";
    }
    if (i == 3) {
        var s = "../lab4html/img/img4.jpeg";
    }
    if (i == 4) {
        var s = "../lab4html/img/img5.jpeg";
    }
    if (i == 5) {
        var s = "../lab4html/img/img2.jpeg";
        i = 0
    }
    return s;
}

function changeColor() {
    var l = document.getElementsByClassName('al');
    for (j = 0; j < l.length; j += 1) {
        l[j].style.color = "red";
        l[j].style.borderRadius = '0px';
    }
}