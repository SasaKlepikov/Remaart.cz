jQuery(document).ready(function(){
  if (jQuery("#edit-auto-display").attr("checked")==true) {
    jQuery("#edit-field-product-category").show();
  }
  else {
    jQuery("#edit-field-product-category").hide();
  }
});