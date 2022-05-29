function deleteComment(commentId) {
    if (confirm("Are you sure you want to delete your comment?")) {
        $.ajax({
            url: 'delete',
            method: 'post',
            data: {
                'commentId': commentId
            },
            success: function () {
                location.reload()
            }
        })
    }
}

function addComment() {
    let value = document.getElementById('commentInput').value;
    if (value !== '') {
        $.ajax({
            url: 'comment',
            method: 'post',
            data: {
                'text': value
            },
            success: function () {
                location.reload()
            }
        })
    } else {
        alert("Comment should be non-empty!");
    }
}

function goBack() {
    location.href = "main";
}