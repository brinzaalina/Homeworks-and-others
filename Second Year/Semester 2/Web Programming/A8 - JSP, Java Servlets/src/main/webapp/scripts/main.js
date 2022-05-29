function goToTopic(value) {
    if (value !== '') {
        document.cookie = `topicId=${value}`;
        $(location).attr("href", "topic");
    } else {
        alert("Invalid topic!");
    }
}

function addTopic() {
    let value = document.getElementById("topic").value;
    if (value !== '') {
        $.ajax({
            url: 'addTopic',
            method: 'post',
            data: {
                name: value,
                userId: sessionUserId
            },
            success: function () {
                location.reload();
            }
        })
    } else {
        alert("Topic name should be non-empty!");
    }
}

function logout() {
    if (confirm("Are you sure you want to log out?")) {
        $.ajax({
            url: 'logout',
            method: 'get',
            success: function () {
                $(location).attr("href", "login")
            }
        })
    }
}