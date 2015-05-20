// these are currently loaded in the admin footer - to investigate , can they be included elsewhere in the javascript e.g. script.js
// the function for when the image is uploaded
function stopUpload(url, image_upload_type){
    if (image_upload_type == "main"){
		$('#NodeMainImgSrc').val(url);
		$('.main_img_preview').attr('src',url);
    } else if (image_upload_type == "thumbnail") {
		$('#NodeMainImgThumbnail').val(url);
		$('.main_img_thumbnail_preview').attr('src',url);
    } else if (image_upload_type == "tinymce"){
		var eid = tinymce.activeEditor.editorId;
    	var ed = tinymce.get(eid);
		ed.execCommand('mceInsertContent',false,'<img alt="title" src="'+url+'" />'); 
    }
	
	$.fancybox.close()
}

/*
$('.jq-upload-form').submit(function() {
	if( $('.jq-file-to-upload').val() == "" ){
		$('.jq-upload-validation-message').fadeIn('slow');
		return false;
	}
});

$('.jq-file-to-upload').change(function(){
	if( $('.jq-file-to-upload').val() != "" ){
		$('.jq-upload-validation-message').fadeOut('slow');
	}
});
*/

