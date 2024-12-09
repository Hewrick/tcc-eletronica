$(document).ready(function() {
    const siteBUrl = "http://http://192.168.157.189"; // Endereço do "site B"
    const targetTagId = "#stream"; // ID da tag específica no "site B"

    // Verifica se o site B está disponível
    $.ajax({
        url: siteBUrl,
        method: "GET",
        success: function(data) {
            // Cria um elemento temporário para buscar o conteúdo da tag específica
            const tempTag = $("<img>").html(data);
            const targetContent = tempTag.find(targetTagId).html();

            if (targetContent) {
                // Atualiza o conteúdo da div no site A
                $("#content").html(targetContent);
            } else {
                $("#content").html("Aviso: Problema(s) para transmitir o vídeo.");
            }
        },
        error: function() {
            $("#content").html("Aviso: Câmera indiponível no momento.");
        }
    });
});