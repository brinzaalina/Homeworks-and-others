function isNumeric(n) {
    if (typeof n != "string") {
        return false;
    } else {
        return !isNaN(n) && !isNaN(parseFloat(n));
    }
}

function sortTable(n, nrColumns) {
    var table, rows, switching, i, x, y, shouldSwitch, direction, switchCount = 0;
    table = document.getElementById("myTable");
    switching = true;
    direction = "asc";
    while (switching) {
        switching = false;
        rows = table.rows;
        for (i = 1; i < (rows.length - 1); i++) {
            shouldSwitch = false;
            x = rows[i].getElementsByTagName("td")[n];
            y = rows[i + 1].getElementsByTagName("td")[n];
            if (direction == "asc") {
                if (!isNumeric(x.innerHTML) && !isNumeric(y.innerHTML)) {
                    if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()) {
                        shouldSwitch = true;
                        break;
                    }
                } else {
                    if (Number(x.innerHTML) > Number(y.innerHTML)) {
                        shouldSwitch = true;
                        break;
                    }
                }
            } else if (direction == "desc") {
                if (!isNumeric(x.innerHTML) && !isNumeric(y.innerHTML)) {
                    if (x.innerHTML.toLowerCase() < y.innerHTML.toLowerCase()) {
                        shouldSwitch = true;
                        break;
                    }
                } else {
                    if (Number(x.innerHTML) < Number(y.innerHTML)) {
                        shouldSwitch = true;
                        break;
                    }
                }
            }
        }

        if (shouldSwitch) {
            rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
            switching = true;
            switchCount++;
        } else {
            if (switchCount == 0 && direction == "asc") {
                direction = "desc";
                switching = true;
            }
        }
    }
    idUp = "column" + (n + 1) + "-up";
    idDown = "column" + (n + 1) + "-down";
    for(i = 1; i <= nrColumns; i++)
            if( n+1 != i){
                idUp2 = "column" + (i) + "-up";
                idDown2 = "column" + (i) + "-down";
                document.getElementById(idUp2).style.visibility = "hidden";
                document.getElementById(idDown2).style.visibility = "hidden";
	    }
    if (direction == "asc") {
        document.getElementById(idUp).style.visibility = "visible";
        document.getElementById(idDown).style.visibility = "hidden";
    } else {
        document.getElementById(idUp).style.visibility = "hidden";
        document.getElementById(idDown).style.visibility = "visible";
    }
}