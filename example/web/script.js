function createAlert(title, message, callback) {
    document.getElementById('alert-title').innerText = title;
    document.getElementById('alert-message').innerText = message;

    const overlay = document.getElementById('alert-overlay');
    overlay.classList.remove('hidden');

    document.getElementById('okay-button').onclick = () => {
        hideAlert();
        callback(true);
    };

    document.getElementById('cancel-button').onclick = () => {
        hideAlert();
        callback(false);
    };
}

function hideAlert() {
    const overlay = document.getElementById('alert-overlay');
    overlay.classList.add('hidden');
}

function showAlert(eventData) {
	const eventDataJson = JSON.parse(eventData);
	const alertId = parseInt(eventDataJson[0]);
	const alertTitle = eventDataJson[1];
	const alertMessage = eventDataJson[2];
	
	createAlert(alertTitle, alertMessage, (response) => {
		let outgoingEventData = new Array();
		outgoingEventData.push(alertId);
		outgoingEventData.push(response);
		
		console.log(`Response status: ${response}`);
		Cef.sendEvent("alert_response", JSON.stringify(outgoingEventData));
	});
}

Cef.registerEventCallback("alert_show", "showAlert");